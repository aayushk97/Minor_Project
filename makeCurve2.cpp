#include<bits/stdc++.h>
#include <vector>

using std::vector;



//define no of control points
//int curveNumPoints = 22;
int curveNumPoints = 7;


//store the control points
/*vector<vector<float>> curveData{ 
    {-0.0029370324, 0.0297554422, 0}, 
    {-0.1556627219, 0.3293327560, 0}, 
    {-0.2613958914, 0.9578577085, 0}, 
    {-0.2555218265, 1.3044275420, 0}, 
    {-0.2496477615, 1.6509973760, 0}, 
    {-0.1262923970, 2.0445597290, 0}, 
    { 0.1791589818, 2.2853963930, 0}, 
    { 0.4846103605, 2.5262330570, 0}, 
    { 0.9427874287, 2.2560260680, 0}, 
    { 1.0132762080, 1.9212043650, 0}, 
    { 1.0837649880, 1.5863826610, 0}, 
    { 0.9369133637, 1.2750572170, 0}, 
    { 0.6667063748, 1.2691831520, 0}, 
    { 0.3964993859, 1.2633090870, 0}, 
    { 0.2320255666, 1.3514200620, 0}, 
    { 0.1850330468, 1.5276420110, 0}, 
    { 0.1380405269, 1.7038639600, 0}, 
    { 0.2026552417, 1.8918340400, 0}, 
    { 0.4082475158, 1.9564487540, 0}, 
    { 0.6138397900, 2.0210634690, 0}, 
    { 0.7606914144, 1.8800859100, 0}, 
    { 0.7606914144, 1.7038639600, 0} 
}; 
*/
/*
Point 0 <Vector (-1.7707, 0.0963, -0.0264)> <Vector (-2.4001, -0.1999, -0.0341)> <Vector (-1.0900, 0.4166, -0.0181)>
Point 1 <Vector (1.0010, 0.0070, -0.0265)> <Vector (0.0926, -0.2800, -0.0348)> <Vector (1.9285, 0.3000, -0.0181)>
Point 2 <Vector (4.3770, -0.0153, -0.0117)> <Vector (3.4689, -0.3409, -0.0043)> <Vector (5.1642, 0.2669, -0.0181)>
Point 3 <Vector (7.6656, -0.0967, 0.0646)> <Vector (6.8455, -0.3973, 0.1202)> <Vector (8.6196, 0.2530, 0.0000)>

*/
vector<vector<float>> curveData{
	{-1.7707, 0.0963, -0.0264},
	{-1.0900, 0.4166, -0.0181},
	{0.0926, -0.2800, -0.0348},
	{1.0010, 0.0070, -0.0265},
	{1.9285, 0.3000, -0.0181},
	{3.4689, -0.3409, -0.0043},
	{4.3770, -0.0153, -0.0117}
};

vector<float> evalBezierCurve(vector<vector<float>>& P, float t){
	float b0 = (1 - t)*(1 - t)*(1 - t);
	float b1 = 3 * t * (1 - t)*(1 - t);
	float b2 = 3 * t * t * (1 - t);
	float b3 = t * t * t;
	
	
	
	return {P[0][0]*b0 + P[1][0] * b1 + P[2][0] * b2 + P[3][0] * b3, 
		P[0][1]*b0 + P[1][1] * b1 + P[2][1] * b2 + P[3][1] * b3,
		P[0][2]*b0 + P[1][2] * b1 + P[2][2] * b2 + P[3][2] * b3} ;

}

vector<float> derivativeBezier(vector<vector<float>> P, float t){

	return {-3 * (1-t)*(1-t) * P[0][0] + ( 3 * (1-t)*(1-t) - 6 * t * (1-t)) * P[1][0] + 
	(6 * t * (1-t) - 3 * t * t) * P[2][0] + 3 * t * t * P[3][0],
	-3 * (1-t)*(1-t) * P[0][1] + ( 3 * (1-t)*(1-t) - 6 * t * (1-t)) * P[1][1] + 
	(6 * t * (1-t) - 3 * t * t) * P[2][1] + 3 * t * t * P[3][1],
	-3 * (1-t)*(1-t) * P[0][2] + ( 3 * (1-t)*(1-t) - 6 * t * (1-t)) * P[1][2] + 
	(6 * t * (1-t) - 3 * t * t) * P[2][2] + 3 * t * t * P[3][2]};
}

vector<float> normalize(vector<float> point){
	
	float w = sqrt(point[0]*point[0] + point[1]* point[1] + point[2]*point[2]);
	point[0] /= w;
	point[1] /= w;
	point[2] /= w;
	
	return {point[0], point[1], point[2]};
}

vector<float> crossProduct(vector<float> u, vector<float> v){
	float a = u[1]*v[2] - u[2]*v[1];
	float b = u[2]*v[0] - u[0]*v[2];
	float c = u[0]*v[1] - u[1]*v[0];
	
	return {a, b, c}; 
}

int main(){

	//resolution of bezier curve
	int ndivs = 16;
	
	//Number of bezier curves used
	int ncurves = 1 + (curveNumPoints - 4)/3;
	
	//define vectors for points, normals and texture coords
	vector<vector<float>> pt((ndivs + 1) * ndivs * ncurves +1);
	vector<vector<float>> normals((ndivs + 1) * ndivs * ncurves + 1);
	vector<vector<float>> st((ndivs + 1) * ndivs * ncurves + 1);
	
	//3D position coords
	vector<vector<float>> controlPoints(4);
	
	for(int i = 0; i < ncurves; i++){
		for(int j = 0; j < ndivs; j++){
			
			//Get the control points of current curve
			controlPoints[0] = curveData[i * 3];
			controlPoints[1] = curveData[i * 3 + 1];
			controlPoints[2] = curveData[i * 3 + 2];
			controlPoints[3] = curveData[i * 3 + 3];
			
			//define the step
			float step = j / (float)ndivs;
			
			//evaluate the bezier curve to generate the curve at that step
			vector<float> point = evalBezierCurve(controlPoints, step);
			
			//Get the tangents at that point
			vector<float> tangent = normalize(derivativeBezier(controlPoints, step));
			
			//create a local coordinate system for this step
			bool swap = false;
			
			
			
			//we find the tangent coordinate which is highest in val
			int maxAxis; // x is 0, y is 1, z is 2
			
			if(abs(tangent[0]) > abs(tangent[1])){
				if(abs(tangent[0]) > abs(tangent[2])){
					maxAxis = 0;
				}else{
					maxAxis = 2;
				} 
			}else if(abs(tangent[1]) > abs(tangent[2])){
				maxAxis = 1;
				
			}else maxAxis = 2;
			
			
			vector<float> up(3, 0), forward(3, 0), right(3, 0);
			
			switch(maxAxis){
				case 0:
				case 1:
					up = tangent;
					forward[2] = 1; // i.e forward is set to 0, 0, 1
					right = crossProduct(up, forward);
					forward = crossProduct(right, up);
					break;
				case 2:
					up = tangent;
					right[2] = 1;
					forward = crossProduct(right, up);
					right = crossProduct(up, forward);
					break;
				default:
					break;
					
				
			}
			
			
			//generate a cicle of verticles around this coordinate system
			//we want to curves to be thinner as we go up towards the tip
			
			//check this to change radius of cicle ar each strp for each curve
			float sNormalized = (i * ndivs + j) / (float)(ndivs* ncurves);
			
			//float radius = 0.1 * (1 - 0.5*sNormalized );
			float radius = 0.2 * (1 - 0.5*sNormalized); 
			for(int k = 0; k <= ndivs; k++){
				float t = k / (float) ndivs;
				float theta = t * 2 * M_PI;
				
				//get points of circle at each step
				vector<float> pc{(float)cos(theta)*radius, 0, (float)sin(theta)*radius};
				
				float x = pc[0]*right[0] + pc[1]*up[0]+pc[2]*forward[0];
				float y = pc[0]*right[1] + pc[1]*up[1] + pc[2]*forward[1];
				float z = pc[0]* right[2] + pc[1]*up[2] + pc[2]*forward[2];
				
				//we then translate these points
				//vector<float> temp1{, point[1] + y,point[2] + z};
				//std::cout<<<<std::endl;
				pt[i * (ndivs + 1) * ndivs + j * (ndivs + 1) + k].push_back({point[0] + x});
				pt[i * (ndivs + 1) * ndivs + j * (ndivs + 1) + k].push_back({point[1] + y});
				pt[i * (ndivs + 1) * ndivs + j * (ndivs + 1) + k].push_back({point[2] + z});
				
				
				vector<float> unitNormal(normalize({x, y, z}));		
				normals[i * (ndivs + 1) * ndivs + j * (ndivs + 1) + k].push_back(unitNormal[0]);
				normals[i * (ndivs + 1) * ndivs + j * (ndivs + 1) + k].push_back(unitNormal[1]);
				normals[i * (ndivs + 1) * ndivs + j * (ndivs + 1) + k].push_back(unitNormal[2]);
				
				
				st[i * (ndivs + 1) * ndivs + j * (ndivs + 1) + k].push_back(sNormalized);
				st[i * (ndivs + 1) * ndivs + j * (ndivs + 1) + k].push_back(t*(radius/0.2)+sNormalized/2);
				
			
			}
		
		}
	}
	
	//Meshing
	pt[(ndivs + 1) * ndivs * ncurves] = curveData[curveNumPoints - 1];
	normals[(ndivs + 1) * ndivs * ncurves] = normalize({curveData[curveNumPoints - 2][0] - curveData[curveNumPoints - 1][0], 
	curveData[curveNumPoints - 2][1] - curveData[curveNumPoints - 1][1],
	curveData[curveNumPoints - 2][2] - curveData[curveNumPoints - 1][2]});
	
	
	st[(ndivs + 1) * ndivs * ncurves].push_back(1);
	st[(ndivs + 1) * ndivs * ncurves].push_back(0.5);
	
	
	
	//calculate the no of faces in our mesh
	int numFaces = ndivs * ndivs * ncurves;
	
	vector<int> verts(numFaces);
	
	for(int i = 0; i < numFaces; i++){
		//if it has to be rendered with a square or a triangle i.e last polygon
		verts[i] = ( i < (numFaces - ndivs)) ? 4 : 3;
	}	
		vector<int> vertIndices(ndivs * ndivs * ncurves * 6 + ndivs * 3);
		
		int nf = 0, ix = 0;
		
		for(int k = 0; k < ncurves; k++){
			for(int j = 0; j < ndivs; j++){
				
				if(k == (ncurves -1) && j == (ndivs - 1)) break;
				
				for(int i = 0; i < ndivs; i++){
					vertIndices[ix] = nf;
					vertIndices[ix + 1] = nf + (ndivs + 1);
					vertIndices[ix + 2] = nf + (ndivs + 1) + 1;
					
					vertIndices[ix + 3] = nf;
					vertIndices[ix + 4] = nf + (ndivs + 1) + 1;
					vertIndices[ix + 5] = nf + 1;
					
					ix += 6;
					nf++;
				}
				nf++;
			
			}
		
		}
		
		for(int i = 0; i < ndivs; i++){
			vertIndices[ix] = nf;
			vertIndices[ix + 1] = (ndivs + 1) * ndivs * ncurves;
			vertIndices[ix + 2] = nf + 1;
			ix += 3;
			nf++;
		}
		
		for(int k = 0; k < vertIndices.size(); k++){
			int x = vertIndices[k];
			
			std::cout<<pt[x][0]*20<<" ";
	 		std::cout<<pt[x][1]*20<<" ";
	 		std::cout<<pt[x][2]*20<<" ";
	 	
	 		std::cout<<st[x][0]<<" ";
	 		std::cout<<st[x][1]<<" ";
	 	
	 		std::cout<<normals[x][0]<<" ";
	 		std::cout<<normals[x][1]<<" ";
	 		std::cout<<normals[x][2]<<" ";
			
		}
	
	std::cout<<"vert size: "<<vertIndices.size();
}
/*
import bpy
myCurve = bpy.data.curves[0] # here your curve
spline= myCurve.splines[0] # maybe you need a loop if more than 1 spline

print("\n======================")
for x in range(len(spline.bezier_points)):
    print("Point " + str(x)
        ,spline.bezier_points[x].co
        ,spline.bezier_points[x].handle_left
        ,spline.bezier_points[x].handle_right)

*/

#include "FreeCamera.hpp"

FreeCamera::FreeCamera(){
	// Stubby for now! Hooray!
}

void FreeCamera::update(){
	// Calculate the direction vector of the lookat
	float directionVectorX = sin(theta) * sin(phi);
    float directionVectorY = -1 * cos(phi);
    float directionVectorZ = -1 * cos(theta) * sin(phi);
    float magnitude = sqrt((directionVectorX * directionVectorX) + (directionVectorY * directionVectorY) + (directionVectorZ * directionVectorZ));

    // and NORMALIZE the directional vector
    lookAtX = directionVectorX / magnitude;
    lookAtY = directionVectorY / magnitude;
    lookAtZ = directionVectorZ / magnitude;
}

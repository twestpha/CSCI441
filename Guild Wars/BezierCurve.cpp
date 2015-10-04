#include "BezierCurve.hpp"
#include "Point.hpp"

BezierCurve::BezierCurve(){
	controlCageIsVisible = false;
	curveIsVisible = false;
}

BezierCurve::BezierCurve(std::vector<Point> control_points){
	controlCageIsVisible = false;
	curveIsVisible = false;
	this->control_points = control_points;
}

void BezierCurve::draw(int resolution){
	if(controlCageIsVisible){
		drawPoints();
		drawControlCage();
	}
	if(curveIsVisible){
		drawCurve(resolution);
	}
}

void BezierCurve::toggleControlCageVisibility(){
	controlCageIsVisible=!controlCageIsVisible;
}

void BezierCurve::toggleCurveVisibility(){
	curveIsVisible=!curveIsVisible;
}

void BezierCurve::drawPoints(){
	for(unsigned int i(0); i < control_points.size(); ++i){
		glPushMatrix();
			// Translate our sphere
			Point p = control_points[i];
	    	glTranslatef(p.getX(), p.getY(), p.getZ());

	    	// Draw the sphere for the point itself
	    	glColor3f(0.0, 1.0, 0.0);
	    	glutSolidSphere(0.5, 16, 16);
	    glPopMatrix();
	}
}

void BezierCurve::drawControlCage(){
	glDisable( GL_LIGHTING );

	for(unsigned int j(1); j < control_points.size(); ++j){
		Point a = control_points[j];
		Point b = control_points[j - 1];

		glColor3f(1.0, 1.0, 0.0);
    	glLineWidth(3.0);

    	glBegin(GL_LINES);
   	 		glVertex3f(a.getX(), a.getY(), a.getZ());
    		glVertex3f(b.getX(), b.getY(), b.getZ());
    	glEnd();
	}

	glEnable( GL_LIGHTING );
}

void BezierCurve::drawCurve(int resolution){

	if( (control_points.size() - 4) % 3 != 0 || control_points.size() < 4){
		printf("Wrong number of control points.\n");
	}

	glDisable( GL_LIGHTING );

	Point lastPoint = control_points.front();
	Point nextPoint;

	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(1.0);

	// First, let's get the number of "chunks" of 4 points we need
	for( unsigned int i(3); i < control_points.size(); i+=3){
		// Chunk of 4

		Point a = control_points[i-3];
		Point b = control_points[i-2];
		Point c = control_points[i-1];
		Point d = control_points[i];

		for(int j(0); j < resolution; ++j){

			float t = float(j)/float(resolution);

			nextPoint = interpolatePointFromCurveAlongT(a, b, c, d, t);

			glBegin(GL_LINES);
				glVertex3f(lastPoint.getX(), lastPoint.getY(), lastPoint.getZ());
				glVertex3f(nextPoint.getX(), nextPoint.getY(), nextPoint.getZ());
			glEnd();

			lastPoint = nextPoint;
		}
	}

	nextPoint = control_points.back();
	glBegin(GL_LINES);
		glVertex3f(lastPoint.getX(), lastPoint.getY(), lastPoint.getZ());
		glVertex3f(nextPoint.getX(), nextPoint.getY(), nextPoint.getZ());
	glEnd();

	glEnable( GL_LIGHTING );
}

Point BezierCurve::getPointFromT(float t){
	// Which chunk are we on?
	int number_chunks = ((control_points.size() - 4) / 3) + 1;
	int which_chunk = int(float(number_chunks)*t);
	float t_per_chunk = 1.0/float(number_chunks);
	float normalized_t = t - (t_per_chunk * which_chunk);
	normalized_t/=t_per_chunk;

	Point a = control_points[(which_chunk*3)+0];
	Point b = control_points[(which_chunk*3)+1];
	Point c = control_points[(which_chunk*3)+2];
	Point d = control_points[(which_chunk*3)+3];

	return interpolatePointFromCurveAlongT(a, b, c, d, normalized_t);
}

Point BezierCurve::interpolatePointFromCurveAlongT(Point a, Point b, Point c, Point d, float t){
	return ((-1*a + 3*b - 3*c + d)*(t*t*t)) +
					((3*a - 6*b + 3*c)*(t*t)) +
					((-3*a + 3*b)*(t)) +
					(a);
}

// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <GL/glu.h>

#include "modelerglobals.h"

void drawTriangle(const double p1[3], const double p2[3], const double p3[3]) {
	drawTriangle(p1[0], p1[1], p1[2], p2[0], p2[1], p2[2], p3[0], p3[1], p3[2]);
}

void drawTrapezoidPrism(double h, double w1, double l1, double w2, double l2)
{
	double a[3] = { -w1 / 2,h / 2,-l1 / 2 };
	double b[3] = { w1 / 2,h / 2,-l1 / 2 };
	double c[3] = { w1 / 2,h / 2,l1 / 2 };
	double d[3] = { -w1 / 2,h / 2,l1 / 2 };
	double e[3] = { -w2 / 2,-h / 2,-l2 / 2 };
	double f[3] = { w2 / 2,-h / 2,-l2 / 2 };
	double g[3] = { w2 / 2,-h / 2,l2 / 2 };
	double hp[3] = { -w2 / 2,-h / 2,l2 / 2 };
	glPushMatrix();
	//12 triangles

	drawTriangle(a, c, b);
	drawTriangle(a, d, c);

	drawTriangle(a, b, f);
	drawTriangle(a, e, f);
	drawTriangle(b, c, g);
	drawTriangle(b, g, f);
	drawTriangle(c, d, hp);
	drawTriangle(c, g, hp);
	drawTriangle(d, a, e);
	drawTriangle(d, e, hp);

	drawTriangle(e, g, f);
	drawTriangle(e, hp, g);

	glPopMatrix();
}

void drawTrapezoidPrismShift_w(double h, double w1, double l1, double w2, double l2)
{
	double a[3] = { 0,h / 2,-l1 / 2 };
	double b[3] = { w1 ,h / 2,-l1 / 2 };
	double c[3] = { w1 ,h / 2,l1 / 2 };
	double d[3] = { 0,h / 2,l1 / 2 };
	double e[3] = { 0,-h / 2,-l2 / 2 };
	double f[3] = { w2 ,-h / 2,-l2 / 2 };
	double g[3] = { w2 ,-h / 2,l2 / 2 };
	double hp[3] = {0,-h / 2,l2 / 2 };
	glPushMatrix();
	//12 triangles

	drawTriangle(a, c, b);
	drawTriangle(a, d, c);

	drawTriangle(a, b, f);
	drawTriangle(a, e, f);
	drawTriangle(b, c, g);
	drawTriangle(b, g, f);
	drawTriangle(c, d, hp);
	drawTriangle(c, g, hp);
	drawTriangle(d, a, e);
	drawTriangle(d, e, hp);

	drawTriangle(e, g, f);
	drawTriangle(e, hp, g);

	glPopMatrix();
}

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
    ModelerView::draw();
	//background color
	//glClearColor(1.0, 1.0, 1.0, 1.0);

	// draw the floor
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
		glTranslated(-10,0,-10);
		drawBox(20,0.01f,20);
	glPopMatrix();

	// draw the model
	setAmbientColor(.1f,.1f,.1f);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
		// float skinColor[3] = { (float)255 / 255, (float)224 / 255, (float)190 / 255 };//more like human
		float skinColor[3] = { (float)243 / 255, (float)225 / 255, (float)210 / 255 };
		//float skinColor[3] = { (float)252 / 255, (float)243 / 255, (float)235 / 255 };//more pale
		float clothesColor[3] = { (float)15 / 255, (float)10 / 255, (float)10 / 255 };

		//1 unit = 10 cm
		float headRadius = VAL(HEADRADIUS);
		float torseWidth = 20 * 0.1;
		float bodyThickness = VAL(BODYTHICKNESS) * 0.1;
		float chestHeight = 18 * 0.1;
		float shoulderClothesRadius = 4 * 0.1;
		float shoulderRadius = 3 * 0.1;
		float waistHeight_upper = 12 * 0.1;
		float waistHeight_lower = 10 * 0.1;
		float armRadius = 2.5 * 0.1;
		float armLength = 25 * 0.1;
		float thighHeight = VAL(THIGHHEIGHT) * 0.1;
		float legHeight = VAL(LEGHEIGHT) * 0.1;
		float pantsRatio = 0.3;
		float footHeight = 5 * 0.1;
		float hipRadius = 7 * 0.1;
		float thighRadius = 6 * 0.1; 
		float legRadius = 3.5 * 0.1;
		float footRadius = 2 * 0.1;
		float hipShift = torseWidth / 4; 
		float toeHeight = 0.2;
		float headScale = VAL(HEADSCALE);
		//upper body
		glPushMatrix();
			glTranslated(0, footHeight+ legHeight+ thighHeight+ hipShift / 2 + waistHeight_lower+ waistHeight_upper+ chestHeight, 0.0);
			glRotated(VAL(UPPERBODYANGLE), 0, 1, 0);
			//head and neck
			glPushMatrix();
				if (VAL(LOD) > 1) {
				glTranslated(0.0, 2.0, 0.0);
				// draw head
				glPushMatrix();
					setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
					glScaled(1, headScale,1);
					glTranslated(0, -headRadius *headScale/2, headRadius*0.1);
					drawSphere(headRadius);
				glPopMatrix();
				// draw neck
				glPushMatrix();
					glTranslated(0, -headRadius*headScale *3/4, -headRadius*0.1);
					glRotated(90, 1.0, 0.0, 0.0);
					setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
					drawCylinder(1.75, 0.28, 0.32);
				glPopMatrix();
				}
			glPopMatrix();

			//torso and arms
			glPushMatrix();
				if (VAL(LOD) >0) {
				//upper torso
				glPushMatrix();
					setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
					if (VAL(LOD) >1) {
					//chest
					glPushMatrix();
						glTranslated(0.0, -chestHeight/2, 0.0);
						drawTrapezoidPrism(chestHeight, torseWidth, bodyThickness*4/5, torseWidth , bodyThickness);
					glPopMatrix();
					//waist
					glPushMatrix();
						glTranslated(0.0, -chestHeight - waistHeight_upper /2, 0.0);
						drawTrapezoidPrism(waistHeight_upper, torseWidth, bodyThickness, torseWidth*3/4, bodyThickness*3/4);
					glPopMatrix();
					glPushMatrix();
						glTranslated(0.0, -chestHeight - waistHeight_upper - waistHeight_lower /2, 0.0);
						drawTrapezoidPrism(waistHeight_lower, torseWidth * 3 / 4, bodyThickness * 3 / 4, torseWidth, bodyThickness);
					glPopMatrix();
					}
				glPopMatrix();
				glPushMatrix();//arms
					if (VAL(LOD) >1) {
					glPushMatrix();//right arm
						glTranslated(torseWidth / 2 + armRadius, 0, 0);
						//shoulder
						setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
						glTranslated(0, -shoulderRadius, 0);
						drawSphere(shoulderClothesRadius);
						setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
						glRotated(90.0, 1.0, 0.0, 0.0);
						//right upper arm
						drawCylinder(armLength, shoulderRadius, armRadius);
						//right forearm
						if (VAL(LOD) >2) {
						glPushMatrix();
							glTranslated(0.0, 0, armLength);
							drawCylinder(armLength, armRadius, armRadius);
						glPopMatrix();
						}
					glPopMatrix();
					glPushMatrix();//left arm
						glTranslated(-torseWidth / 2 - armRadius, 0, 0);
						//shoulder
						setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
						glTranslated(0, -shoulderRadius, 0);
						drawSphere(shoulderClothesRadius);
						setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
						glRotated(90.0, 1.0, 0.0, 0.0);
						drawCylinder(armLength, shoulderRadius, armRadius);//left upper arm
						//left forearm
						if (VAL(LOD) >2) {
						glPushMatrix();
							glTranslated(0.0, 0, armLength);
							drawCylinder(armLength, armRadius, armRadius);
						glPopMatrix();
						}
					glPopMatrix();
					}
				glPopMatrix();//end of arms
				}
			glPopMatrix();//arms and torso
		glPopMatrix();//end of upper body
		//lower body
		glPushMatrix();
			setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
			glTranslated(0, footHeight + legHeight + thighHeight + hipShift / 2, 0.0);
			if (VAL(LOD) >0) {
			glPushMatrix();//hip
				glTranslated(0, 0, -hipShift*0.15);		
				if (VAL(LOD) > 1) {
				glPushMatrix();//right
					glTranslated(hipShift, 0, 0);
					drawSphere(hipRadius);
				glPopMatrix();
				glPushMatrix();//left
					glTranslated(-hipShift, 0, 0);
					drawSphere(hipRadius);
				glPopMatrix();
				}
			glPopMatrix();//end of hip
			}
			glPushMatrix();//legs
				if (VAL(LOD) >1) {
				glPushMatrix();//right leg
					glTranslated(-thighRadius, 0, 0);
					//pants
					glRotated(90.0+ VAL(RIGHTTHIGHANGLE), 1.0, 0.0, 0.0);
					glTranslated(0, 0, hipShift / 2);
					setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
					drawCylinder(thighHeight * pantsRatio, thighRadius, thighRadius*pantsRatio +legRadius*(1- pantsRatio));
					//thigh
					glTranslated(0, 0, thighHeight * pantsRatio);
					setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
					drawCylinder(thighHeight * (1-pantsRatio), thighRadius*pantsRatio + legRadius*(1 - pantsRatio), legRadius);
					//knee
					glTranslated(0, 0, thighHeight * (1 - pantsRatio));
					drawSphere(legRadius);
					//right leg
					if (VAL(LOD) >2) {
					glPushMatrix();
						setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
						glRotated(VAL(RIGHTLEGANGLE), 1, 0, 0);
						drawCylinder(legHeight, legRadius, footRadius);
						//ankle
						glTranslated(0, 0, legHeight);
						drawSphere(footRadius);
						if (VAL(LOD) >3) {
						glPushMatrix();//foot
							setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
							glTranslated(0, -footRadius, (footHeight - 0.2) / 2);
							glRotated(-90, 0, 1, 0);
							glRotated(90, 0, 0, 1);
							drawTrapezoidPrismShift_w((footHeight - toeHeight), footRadius * 2, footRadius * 2, 2, footRadius * 2);
							glTranslated(0, -((footHeight - toeHeight) / 2 + toeHeight / 2), 0 );
							drawTrapezoidPrismShift_w(toeHeight, 2, footRadius * 2, 2, footRadius * 2);
						glPopMatrix();//end of foot
						}
					glPopMatrix();//end of right leg
					}
				glPopMatrix();//end of right leg
				}
				if (VAL(LOD) >1) {
					glPushMatrix();//left leg
					glTranslated(thighRadius, 0, 0);
					//pants
					glRotated(90.0 + VAL(LEFTTHIGHANGLE), 1.0, 0.0, 0.0);
					glTranslated(0, 0, hipShift / 2);
					setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
					drawCylinder(thighHeight * pantsRatio, thighRadius, thighRadius*pantsRatio + legRadius*(1 - pantsRatio));
					//thigh
					glTranslated(0, 0, thighHeight * pantsRatio);
					setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
					drawCylinder(thighHeight * (1 - pantsRatio), thighRadius*pantsRatio + legRadius*(1 - pantsRatio), legRadius);
					//knee
					glTranslated(0, 0, thighHeight * (1 - pantsRatio));
					drawSphere(legRadius);
					//right leg
					if (VAL(LOD) >2) {
						glPushMatrix();
						setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
						glRotated(VAL(LEFTLEGANGLE), 1, 0, 0);
						drawCylinder(legHeight, legRadius, footRadius);
						//ankle
						glTranslated(0, 0, legHeight);
						drawSphere(footRadius);
						if (VAL(LOD) >3) {
							glPushMatrix();//foot
							setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
							glTranslated(0, -footRadius, (footHeight - 0.2) / 2);
							glRotated(-90, 0, 1, 0);
							glRotated(90, 0, 0, 1);
							drawTrapezoidPrismShift_w((footHeight - toeHeight), footRadius * 2, footRadius * 2, 2, footRadius * 2);
							glTranslated(0, -((footHeight - toeHeight) / 2 + toeHeight / 2), 0);
							drawTrapezoidPrismShift_w(toeHeight, 2, footRadius * 2, 2, footRadius * 2);
							glPopMatrix();//end of foot
						}
						glPopMatrix();//end of left leg
					}
					glPopMatrix();//end of left leg
				}
			glPopMatrix();//end of legs
		glPopMatrix();// end of lower body
	
		
	    //test
		glPushMatrix();

		glTranslated(3, 3, 3);
		drawTorus(0.5, 2);

		glPopMatrix();

		//test end	
		
		
	glPopMatrix();

}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];
	controls[LOD] = ModelerControl("Level of Detail", 0, 4, 1.0f, 4);
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[HEADRADIUS] = ModelerControl("Head Radius", 0.5, 1.5, 0.1f, 0.9f);
	controls[HEADSCALE] = ModelerControl("Head Y-Sccale", 1, 1.5, 0.1f, 1.2f);
	controls[BODYTHICKNESS] = ModelerControl("Body Thickness", 8, 18, 0.1f, 13.0);
	controls[THIGHHEIGHT] = ModelerControl("Thigh Length", 20, 60, 0.1f, 40.0);
	controls[LEGHEIGHT] = ModelerControl("Leg Length", 20, 60, 0.1f, 35.0);
	controls[RIGHTTHIGHANGLE] = ModelerControl("Right Thigh Angle", -90, 90, 1, 0.0);
	controls[LEFTTHIGHANGLE] = ModelerControl("Left Thigh Angle", -90, 90, 1, 0.0);
	controls[RIGHTLEGANGLE] = ModelerControl("Right Leg Angle", 0, 90, 1, 0.0);
	controls[LEFTLEGANGLE] = ModelerControl("Left Leg Angle", 0, 90, 1, 0.0);
	controls[UPPERBODYANGLE] = ModelerControl("Upper Body Angle", -90, 90, 1, 0.0);
    //controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	//controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);

	controls[FRAMEALL] = ModelerControl("Frame All", 0, 1, 1, 0);

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
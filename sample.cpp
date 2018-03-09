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
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// draw the floor
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_GREEN);
	glPushMatrix();
		glTranslated(-10,0,-10);
		drawBox(20,0.01f,20);
	glPopMatrix();

	// draw the sample model
	setAmbientColor(.1f,.1f,.1f);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
		/*sample
		glPushMatrix();
		glTranslated(-1.5, 0, -2);
		glScaled(3, 1, 4);
		drawBox(1,1,1);
		glPopMatrix();
		// draw cannon
		glPushMatrix();
		glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
		glRotated(-90, 1.0, 0.0, 0.0);
		drawCylinder(VAL(HEIGHT), 0.1, 0.1);
		glTranslated(0.0, 0.0, VAL(HEIGHT));
		drawCylinder(1, 1.0, 0.9);

		glTranslated(0.0, 0.0, 0.5);
		glRotated(90, 1.0, 0.0, 0.0);
		drawCylinder(4, 0.1, 0.2);
		glPopMatrix();
		*/

		float skinColor[3] = { (float)255 / 255, (float)224 / 255, (float)190 / 255 };
		float clothesColor[3] = { (float)15 / 255, (float)10 / 255, (float)10 / 255 };

		//1 unit = 10 cm
		float headRadius = 0.9;
		float torseWidth = 20 * 0.1;
		float bodyThickness = 13 * 0.1;
		float chestHeight = 18 * 0.1;
		float shoulderRadius = 4 * 0.1;
		float waistHeight_upper = 12 * 0.1;
		float waistHeight_lower = 10 * 0.1;
		float armRadius = 3 * 0.1;
		float armLength = 25 * 0.1;
		float thighHeight = 40 * 0.1;
		float legHeight = 35 * 0.1;
		float pantsRatio = 0.3;
		float footHeight = 5 * 0.1;
		float hipRadius = 8 * 0.1;
		float thighRadius = 6 * 0.1; 
		float legRadius = 3.5 * 0.1;
		float footRadius = 2 * 0.1;
		float hipShift = torseWidth / 4; 
		float toeHeight = 0.2;

		//upper body
		glPushMatrix();
			glTranslated(0, footHeight+ legHeight+ thighHeight+ hipShift / 2 + waistHeight_lower+ waistHeight_upper+ chestHeight, 0.0);
			//head and neck
			glPushMatrix();
				glTranslated(0.0, 2.0, 0.0);
				// draw head
				glPushMatrix();
					setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
					drawSphere(headRadius);
				glPopMatrix();
				// draw neck
				glPushMatrix();
					glTranslated(0, -headRadius*3/4, 0.0);
					glRotated(90, 1.0, 0.0, 0.0);
					setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
					drawCylinder(1.5, 0.3, 0.4);
				glPopMatrix();
			glPopMatrix();

			//torso and arms
			glPushMatrix();
				//upper torso
				glPushMatrix();
					setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
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
				glPopMatrix();
				glPushMatrix();//arms
					glPushMatrix();//right arm
						glTranslated(torseWidth / 2 + armRadius, 0, 0);
						//shoulder
						setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
						glTranslated(0, -shoulderRadius, 0);
						drawSphere(shoulderRadius);
						setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
						glRotated(90.0, 1.0, 0.0, 0.0);
						//right upper arm
						drawCylinder(armLength, shoulderRadius, armRadius);
						//right forearm
						glPushMatrix();
							glTranslated(0.0, 0, armLength);
							drawCylinder(armLength, armRadius, armRadius);
						glPopMatrix();
					glPopMatrix();
					glPushMatrix();//left arm
						glTranslated(-torseWidth / 2 - armRadius, 0, 0);
						//shoulder
						setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
						glTranslated(0, -shoulderRadius, 0);
						drawSphere(shoulderRadius);
						setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
						glRotated(90.0, 1.0, 0.0, 0.0);
						drawCylinder(armLength, shoulderRadius, armRadius);//left upper arm
						//left forearm
						glPushMatrix();
							glTranslated(0.0, 0, armLength);
							drawCylinder(armLength, armRadius, armRadius);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();//end of arms
			glPopMatrix();//arms and torso
		glPopMatrix();//end of upper body
		//lower body
		glPushMatrix();
			setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
			glTranslated(0, footHeight + legHeight + thighHeight + hipShift / 2, 0.0);
			glPushMatrix();//hip
				glPushMatrix();//right
					glTranslated(hipShift, 0, 0);
					drawSphere(hipRadius);
				glPopMatrix();
				glPushMatrix();//left
					glTranslated(-hipShift, 0, 0);
					drawSphere(hipRadius);
				glPopMatrix();
			glPopMatrix();//end of hip
			glPushMatrix();//legs
				glPushMatrix();//right leg
					glTranslated(-thighRadius, 0, 0);
					glPushMatrix();//right thigh
						//pants
						glRotated(90.0, 1.0, 0.0, 0.0);
						glTranslated(0, 0, hipShift / 2);
						glPushMatrix();//pants
							setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
							drawCylinder(thighHeight * pantsRatio, thighRadius, thighRadius*pantsRatio +legRadius*(1- pantsRatio));
						glPopMatrix();
						glTranslated(0, 0, thighHeight * pantsRatio);
						setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
						glPushMatrix();//thigh
							drawCylinder(thighHeight * (1-pantsRatio), thighRadius*pantsRatio + legRadius*(1 - pantsRatio), legRadius);
						glPopMatrix();
						//knee
						drawSphere(legRadius);
						//right leg
						setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
						glTranslated(0, 0, thighHeight * (1 - pantsRatio));
						glPushMatrix();
							drawCylinder(legHeight, legRadius, footRadius);
						glPopMatrix();
						//ankle
						glTranslated(0, 0, legHeight);
						drawSphere(footRadius);
						glPushMatrix();//foot
							glTranslated(0, -footRadius, (footHeight-0.2)/2);
							glRotated(-90, 0, 1, 0);
							glRotated(90, 0, 0, 1);
							drawTrapezoidPrismShift_w((footHeight- toeHeight), footRadius*2, footRadius*2, 2, footRadius*2);
							glTranslated(0,-((footHeight - toeHeight) / 2+ toeHeight /2),0);
							drawTrapezoidPrismShift_w(toeHeight, 2, footRadius * 2, 2, footRadius * 2);
						glPopMatrix();//end of foot
					glPopMatrix();//end of right thigh
				glPopMatrix();//end of right leg

				glPushMatrix();//left leg
					glTranslated(thighRadius, 0, 0);
					glPushMatrix();//left thigh
						//pants
						glRotated(90.0, 1.0, 0.0, 0.0);
						glTranslated(0, 0, hipShift / 2);
						glPushMatrix();//pants
							setDiffuseColor(clothesColor[0], clothesColor[1], clothesColor[2]);
							drawCylinder(thighHeight * pantsRatio, thighRadius, thighRadius*pantsRatio + legRadius*(1 - pantsRatio));
						glPopMatrix();
						glTranslated(0, 0, thighHeight * pantsRatio);
						setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
						glPushMatrix();//thigh
							drawCylinder(thighHeight * (1 - pantsRatio), thighRadius*pantsRatio + legRadius*(1 - pantsRatio), legRadius);
						glPopMatrix();
						//knee
						drawSphere(legRadius);
						//right leg
						setDiffuseColor(skinColor[0], skinColor[1], skinColor[2]);
						glTranslated(0, 0, thighHeight * (1 - pantsRatio));
						glPushMatrix();
							drawCylinder(legHeight, legRadius, footRadius);
						glPopMatrix();
						//ankle
						glTranslated(0, 0, legHeight);
						drawSphere(footRadius);
						glPushMatrix();//foot
							glTranslated(0, -footRadius, (footHeight - 0.2) / 2);
							glRotated(-90, 0, 1, 0);
							glRotated(90, 0, 0, 1);
							drawTrapezoidPrismShift_w((footHeight - toeHeight), footRadius * 2, footRadius * 2, 2, footRadius * 2);
							glTranslated(0, -((footHeight - toeHeight) / 2 + toeHeight / 2), 0);
							drawTrapezoidPrismShift_w(toeHeight, 2, footRadius * 2, 2, footRadius * 2);
						glPopMatrix();//end of foot
					glPopMatrix();//end of left thigh
				glPopMatrix();//end of left leg

			glPopMatrix();//end of legs
		glPopMatrix();// end of lower body
	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
    controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
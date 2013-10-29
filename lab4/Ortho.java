import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class Ortho {

	private GKS gks;
	private Graphics g;
	private double x, y, z;
	private double sx, px, sy, py;
	public int w, h;
	private MT3D mt3d;
	private Color c;
	private double[][] matrix = {{1, 0, 0, 0}, 
								 {0, 1, 0, 0}, 
								 {0, 0, 1, 0},
								 {0, 0, 0, 1}
								};
	private double[] vec;
	private double[] vec2;

	private double x0, y0, z0;
	private double[][] cameraMatrix = 	{{1, 0, 0, 0}, 
										 {0, 1, 0, 0}, 
										 {0, 0, 1, 0},
										 {0, 0, 0, 1}
										};
	private double[][] rMatrix = 	{{1, 0, 0, 0}, 
									 {0, 1, 0, 0}, 
									 {0, 0, 1, 0},
									 {0, 0, 0, 1}
									};										

	public Ortho(Graphics g, double xmin, 
				 double xmax, double ymin, 
				 double ymax, int xsize, 
				 int ysize) {
		this.g = g;
		/*this.sx = xsize / (xmax - xmin);
		this.sy = ysize / (ymax - ymin);
		this.px = -sx * xmin;
		this.py = sy * ymax;
		this.w = xsize;
		this.h = ysize;*/
		gks = new GKS(g, xmin, xmax, ymin, ymax, xsize, ysize);
	}
	
    public void postaviNa(double x, double y, double z) {
    	this.x = x;
    	this.y = y;
    	this.z = z;
    }

    public void linijaDo(double x, double y, double z) {
    	vec = new double[] {this.x, this.y, this.z, 1.0};
		vec2 = new double[] {x, y, z, 1.0};
		double[] r1 = gks.mult(vec, this.matrix);
		double[] r2 = gks.mult(vec2, this.matrix);
		//mult again
		r1 = getCameraVector(this.matrix, r1);
		r2 = getCameraVector(this.matrix, r2);
		g.setColor(this.c);
		this.g.drawLine(gks.transformX(r1[0]), gks.transformY(r1[1]),
						gks.transformX(r2[0]), gks.transformY(r2[1]));
    	postaviNa(x, y, z);
    }

    public void trans(MT3D m) {
    	this.mt3d = m;
		double[][] temp = m.getM();
		for (int i = 0; i < temp.length; i++)  {
			for (int j = 0; j < temp.length; j++) {
				this.matrix[i][j] = temp[i][j];
			}
		}
    }

    public void postaviBoju(Color c) {
    	this.c = c;
    }

	public void KSK(double x0, double y0, double z0, 
					 double x1, double y1, double z1, 
					 double Vx, double Vy, double Vz) {
		this.x0 = x0;
		this.y0 = y0;
		this.z0 = z0;
		//calculate n vector
		double[] nVector = normalizeVector(new double[] {x0-x1, y0-y1, z0-z1});
		
		//calculate u vector
		double[] uVector = normalizeVector(
											// V x n
											vectorProduct(
												new double[] {Vx, Vy, Vz},
												nVector
												)
										);

		double [] vVector = vectorProduct(nVector, uVector);
		this.rMatrix = getRMatrix(uVector, vVector, nVector);
		/*
		// from the formula (rightmost one)
		double[] tempVector = 
		cameraMatrix = 
		*/
	}

	public double vectorLength(double[] a) {
		double tempx = Math.pow(a[0], 2);
		double tempy = Math.pow(a[1], 2);
		double tempz = Math.pow(a[2], 2);
		return Math.sqrt(tempx + tempy + tempz);
	}

	public double[] vectorProduct(double[] a, double[] b) {
		double iComponent = a[1]*b[2] - a[2]*b[1];
		double jComponent = a[0]*b[2] - a[2]*b[0];
		double kComponent = a[0]*b[1] - a[1]*b[0];
		return new double[] {iComponent, -jComponent, kComponent};
	}

	public double[] normalizeVector(double[] a) {
		double aVectorLength = vectorLength(a);
		double normalizedX = a[0] / aVectorLength;
		double normalizedY = a[1] / aVectorLength;
		double normalizedZ = a[2] / aVectorLength;
		double[] normalizedVector = new double[] {normalizedX,
												  normalizedY,
												  normalizedZ};
	    return normalizedVector;
	}

	public double[][] getRMatrix(double[] u, double[] v, double[] n) {
		return new double[][] {{u[0], u[1], u[2], 0}, 
							   {v[0], v[1], v[2], 0}, 
							   {n[0], n[1], n[2], 0}, 
							   {0, 0, 0, 1}
							  };
	}

	public double[] getCameraVector(double[][] rMatrix, double[] vector) {
		double[][] temp = new double[][] {{1, 0, 0, -this.x0}, 
										  {0, 1, 0, -this.y0}, 
										  {0, 0, 1, -this.z0},
										  {0, 0, 0, 1}
										 };
	 	double[] tempVector = gks.mult(vector, temp);
	 	double[] result = gks.mult(tempVector, rMatrix);
	 	return result;
	 }

}
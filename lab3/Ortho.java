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

	public Ortho(Graphics g, double xmin, 
				 double xmax, double ymin, 
				 double ymax, int xsize, 
				 int ysize) {
		this.g = g;
		this.sx = xsize / (xmax - xmin);
		this.sy = ysize / (ymax - ymin);
		this.px = -sx * xmin;
		this.py = sy * ymax;
		this.w = xsize;
		this.h = ysize;
	}
	
    public void postaviNa(double x, double y, double z) {
    	this.x = x;
    	this.y = y;
    	this.z = z;
    }

    public void linijaDo(double x, double y, double z) {
    	vec = new double[] {this.x, this.y, this.z, 1.0};
		vec2 = new double[] {x, y, z, 1.0};
		double[] r1 = mult(vec, this.matrix);
		double[] r2 = mult(vec2, this.matrix);
		g.setColor(this.c);
		this.g.drawLine(transformX(r1[0]), transformY(r1[1]),
						transformX(r2[0]), transformY(r2[1]));
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

    public double[] mult(double[] vector, double[][] matrix) {

		double[] res = new double[vector.length];
		for (int i = 0; i < vector.length; i++) {
			for (int j = 0; j < matrix.length; j++) {
				res[i] += matrix[i][j] * vector[j];
			}
		}
		return res;
	}

    /**
	* convert to computer coordinate point
	*/
	public int transformX(double x) {
		return (int) (this.sx * x + px);
	}

	/** 
	* convert to computer coordinate point
	*/
	public int transformY(double y) {
		return  (int) (-(this.sy * y) + py);
	}

    public void postaviBoju(Color c) {
    	this.c = c;
    }

}
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class Persp {

	private GKS gks;
	private Graphics g;
	private double x, y, z;
	public double d;
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

	public Persp(Graphics g, double xmin, 
				 double xmax, double ymin, 
				 double ymax, double d,
				 int xsize, int ysize) {
		this.g = g;
		gks = new GKS(g, xmin, xmax, ymin, ymax, xsize, ysize);
		this.d = d;
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
		r1 = getCameraVector(r1);
		r2 = getCameraVector(r2);
		g.setColor(this.c);
		this.g.drawLine(gks.transformX(r1[0] * (this.d/r1[2]) * (-1)), gks.transformY(r1[1] * (this.d/r1[2]) * (-1)),
						gks.transformX(r2[0] * (this.d/r2[2]) * (-1)), gks.transformY(r2[1] *(this.d/r2[2]) * (-1)));
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

	}

	private double vectorLength(double[] a) {
		double tempx = Math.pow(a[0], 2);
		double tempy = Math.pow(a[1], 2);
		double tempz = Math.pow(a[2], 2);
		return Math.sqrt(tempx + tempy + tempz);
	}

	private double[] vectorProduct(double[] a, double[] b) {
		double iComponent = a[1]*b[2] - a[2]*b[1];
		double jComponent = a[0]*b[2] - a[2]*b[0];
		double kComponent = a[0]*b[1] - a[1]*b[0];
		return new double[] {iComponent, -jComponent, kComponent};
	}

	private double[] normalizeVector(double[] a) {
		double aVectorLength = vectorLength(a);
		double normalizedX = a[0] / aVectorLength;
		double normalizedY = a[1] / aVectorLength;
		double normalizedZ = a[2] / aVectorLength;
		double[] normalizedVector = new double[] {normalizedX,
												  normalizedY,
												  normalizedZ};
	    return normalizedVector;
	}

	private double[][] getRMatrix(double[] u, double[] v, double[] n) {
		return new double[][] {{u[0], u[1], u[2], 0}, 
							   {v[0], v[1], v[2], 0}, 
							   {n[0], n[1], n[2], 0}, 
							   {0, 0, 0, 1}
							  };
	}

	private double[] getCameraVector(double[] vector) {
		double[][] temp = new double[][] {{1, 0, 0, -this.x0}, 
										  {0, 1, 0, -this.y0}, 
										  {0, 0, 1, -this.z0},
										  {0, 0, 0, 1}
										 };
	 	double[] tempVector = gks.mult(vector, temp);
	 	double[] result = gks.mult(tempVector, this.rMatrix);
	 	return result;
	 }

	public void stozac(double r, double h, int n) {
	 	double step = (2.0 * Math.PI)/n;
	 	double phi;
	    double x, y;
	    postaviNa(r * Math.cos(0), r * Math.sin(0), 0);
	    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
	      x = r * Math.cos(phi);
	      y = r * Math.sin(phi);
	      linijaDo(x, y, 0);
	    }
	    postaviNa(0, 0, h);
	    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
	      x = r * Math.cos(phi);
	      y = r * Math.sin(phi);
	      linijaDo(x, y, 0);
	      postaviNa(0, 0, h);
	    }
	 }

	 public void valjak_drawer(double r, double r2, double h, int n, int aux) {
	 	double step = (2.0 * Math.PI)/n;
	 	double phi;
	    double x, y;

	    postaviNa(r * Math.cos(0), r * Math.sin(0), 0);
	    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
	      x = r * Math.cos(phi);
	      y = r * Math.sin(phi);
	      linijaDo(x, y, 0);
	    }

	    /*if (aux == 1) {
		    postaviNa(0, 0, 0);
		    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
		      x = r * Math.cos(phi);
		      y = r * Math.sin(phi);
		      linijaDo(x, y, 0);
		      postaviNa(0, 0, 0);
	    	}	
	    }*/

	    postaviNa(r2 * Math.cos(0), r2 * Math.sin(0), h);
	    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
	      x = r2 * Math.cos(phi);
	      y = r2 * Math.sin(phi);
	      linijaDo(x, y, h);
	    }

	    postaviNa(r * Math.cos(0), r * Math.sin(0), h);
	    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
	      x = r * Math.cos(phi);
	      y = r * Math.sin(phi);
	      postaviNa(r2 * Math.cos(phi), r2 * Math.sin(phi), h);
	      linijaDo(x, y, 0);
	    }

	    if (aux == 1){
		    postaviNa(0, 0, h);
		    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
		      x = r2 * Math.cos(phi);
		      y = r2 * Math.sin(phi);
		      linijaDo(x, y, h);
		      postaviNa(0, 0, h);
		    }
		}

	 }

	 public void valjak(double r, double h, int n) {
	 	valjak_drawer(r, r, h, n, 0);
	 }

	 public void krnjiStozac(double r, double r2, double h, int n) {
	 	valjak_drawer(r, r2, h, n, 1);
	 }

	 public void puni_valjak(double r, double h, int n) {
	 	valjak_drawer(r, r, h, n, 1);
	 }

	 public void kugla(double r, int m, int n) {
	 	kugla_drawer(r, m, n, 1);
	 }

	 public void polukugla(double r, int m, int n) {
	 	kugla_drawer(r, m, n, 0);
	 }

	 /**
	 * @type - half sphere / full sphere
	 */
	 public void kugla_drawer(double r, int m, int n, int type) {
	 	double step = Math.PI/(n+1);
	 	double step2 = Math.PI/(m+1);
	 	double drawStep = 0.01;
	 	double theta = 0;
	    double x, y, z;
	    
	    double limit;
	    if (type == 0) {
	    	limit = Math.PI;
	    } else {
	    	limit = 2.0 * Math.PI;
	    }
	    double phi = 0;
	    for(theta = 0; theta <= limit; theta += step) {
			z = r * Math.cos(theta);
			postaviNa(r * Math.sin(theta) * Math.cos(phi),
					  r * Math.sin(theta) * Math.sin(phi),
					  z);
			for (phi = 0; phi <= limit; phi += drawStep) {
				x = r * Math.cos(phi) * Math.sin(theta);
				y = r * Math.sin(theta) * Math.sin(phi);
				if (phi == 0)
					postaviNa(x, y, z);
				else
					linijaDo(x, y, z);
			}
			
	    }
	    
		for (theta = 0; theta <= limit; theta += step2) {
			postaviNa(0, 0, r);
	     	for(phi = 0; phi <= limit; phi += drawStep) {
		      	z = r * Math.cos(phi);
		      	x = r * Math.sin(phi) * Math.cos(theta);
		      	y = r * Math.sin(phi) * Math.sin(theta);
		      	linijaDo(x, y, z);
		    }
		}
		
 	}

 	
 	public void elipsoid (double a, double b, int m, int n) {
        n++;
        double circle =  2.0 * Math.PI;
        double stepN = circle / n / 2;
        double stepM = (circle + 0.1) / m;
        double x, y, z;
        double ro = 0;

        postaviNa(ro * Math.cos(0), ro * Math.sin(0), 0);
        for(double theta = 0; theta <= circle; theta += stepN) {
            ro = a * Math.sin(theta);  
            postaviNa(ro * Math.cos(0), ro * Math.sin(0), b * Math.cos(theta));
            
            for(double phi = 0; phi <= circle/2 + 0.1; phi += 0.1) {
                x = ro * Math.cos(phi);
                y = ro * Math.sin(phi);
                z = b * Math.cos(theta);
                linijaDo(x, y, z);
            }
        }
        
        for(double theta = 0; theta <= circle; theta += stepM) {
            ro = a * Math.sin(theta);  
            postaviNa(Math.cos(theta) * Math.sin(0) * a, ro * Math.sin(0), b * Math.cos(0));
        
            for(double phi = 0; phi <= circle/2 + 0.1; phi += 0.1) {
                x = a * Math.cos(theta) * Math.sin(phi);
                y = ro * Math.sin(phi);
                z = b * Math.cos(phi);
                linijaDo(x, y, z);
            }
        }
    }

}
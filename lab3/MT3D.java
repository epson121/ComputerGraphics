public class MT3D {

	private double m[][]= new double[4][4];
	private double a, b, c, d;
	private double[] unitVector = new double[3];
	public MT3D() {
		identitet();
	}

	public void pomakni(double px, double py, double pz) {
		identitet();
		m[0][3] = px;
		m[1][3] = py;
		m[2][3] = pz;
	}
	
	public void skaliraj(double sx, double sy, double sz) {
		identitet();
		m[0][0] = sx;
		m[1][1] = sy;
		m[2][2] = sz;
	}
	
	public void rotirajX(double kut) {
		identitet();
		kut = Math.toRadians(kut);
		m[1][1] = Math.cos(kut);
		m[1][2] = -Math.sin(kut);
		m[2][1] = Math.sin(kut);
		m[2][2] = Math.cos(kut);
	}

	public void rotirajY(double kut) {
		identitet();
		kut = Math.toRadians(kut);
		m[0][0] = Math.cos(kut);
		m[0][2] = Math.sin(kut);
		m[2][0] = -Math.sin(kut);
		m[2][2] = Math.cos(kut);
	}

	public void rotirajZ(double kut) {
		identitet();
		kut = Math.toRadians(kut);
		m[0][0] = Math.cos(kut);
		m[0][1] = -Math.sin(kut);
		m[1][0] = Math.sin(kut);
		m[1][1] = Math.cos(kut);
	}

	public void rotiraj(double x1, double y1, double z1, 
						double x2, double y2, double z2, 
						double kut) {
		calcCoefficients(x1, y1, z1, x2, y2, z2);
		MT3D m1 = new MT3D();
	    m1.pomakni(-x1, -y1, -z1);
	    this.rotirajX(Math.toDegrees(Math.asin(this.b / this.d)));
	    this.mult(m1);
	    m1.rotirajY(Math.toDegrees(Math.asin(this.a)) * (-1));
	    m1.mult(this);
	    this.rotirajZ(kut);
	    this.mult(m1);
	    m1.rotirajY(Math.toDegrees(Math.asin(this.a)));
	    m1.mult(this);
	    this.rotirajX(Math.toDegrees(Math.asin((this.b / this.d))) * (-1));
	    this.mult(m1);
	    m1.pomakni(x1, y1, z1);
	    m1.mult(this);
	    this.m = m1.getM();
	}
	
	private void calcCoefficients(double x1, double y1, double z1, 
						 double x2, double y2, double z2) {
		double tempX = Math.pow(x2 - x1, 2);
		double tempY = Math.pow(y2 - y1, 2);
		double tempZ = Math.pow(z2 - z1, 2);
		double denominator = Math.sqrt(tempX + tempY + tempZ);
		this.a = (x2 - x1) / denominator;
		this.b = (y2 - y1) / denominator;
		this.c = (z2 - z1) / denominator;
		this.d = Math.sqrt(Math.pow(this.b, 2) + Math.pow(this.c, 2));
	}

	public void identitet() {
		m[0][0] = 1;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;
		m[1][0] = 0;
		m[1][1] = 1;
		m[1][2] = 0;
		m[1][3] = 0;
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = 1;
		m[2][3] = 0;
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;
	}

	public double[][] getM() {
		return this.m;
	}

	public void mult(MT3D mt) {
       int rows = this.m.length;
       double[][] a = mt.getM();
       double[][] c = new double[4][4];
       for (int i = 0; i < rows; i++) {
           for (int j = 0; j < rows; j++) {
               for (int k = 0; k < rows; k++) {
                   c[i][j] +=  m[i][k] * a[k][j];
               }
           }
       }
       this.m = c;
   }

}
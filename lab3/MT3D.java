public class MT3D {

	private double m[][]= new double[4][4];

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
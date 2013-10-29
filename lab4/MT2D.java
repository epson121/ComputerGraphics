public class MT2D {

	private double m[][]= new double[3][3];

	public MT2D() {
		identitet();
	}

	public void pomakni(double px, double py) {
		identitet();
		m[0][2] = px;
		m[1][2] = py;
	} 
	
	public void skaliraj(double sx, double sy) {
		identitet();
		m[0][0] = sx;
		m[1][1]= sy;
	}
	
	public void zrcaliNaX() {
		identitet();
		m[1][1] = -1;
	}
	
	public void zrcaliNaY() {
		identitet();
		m[0][0] = -1;
	}
	
	public void rotiraj(double kut) {
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
		m[1][0] = 0;
		m[1][1] = 1;
		m[1][2] = 0;
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = 1;
	}

	public double[][] getM() {
		return this.m;
	}

	public void mult(MT2D mt) {
       int rows = 3;
       double[][] a = mt.getM();
       double[][] c = new double[3][3];
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
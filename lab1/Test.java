class Test {
	

	public static void main(String[] args) {
		int w = 500;
		int h = 500;

		int sx = w/10;
	    int sy = h/10;
	    
	    int px = -sx * -5;
	    int py = sy * 5;

	    int x1 = sx*0 + px;
	    int y1 = sy*(-1) * 0 + py; 
	    int x2 = sx*2 + px;
	    int y2 = sy*(-1) * 2 + py;
	    System.out.println("x1: " + x1);
	    System.out.println("y1: " + y1);
	    System.out.println("x2: " + x2);
	    System.out.println("y2: " + y2);
	}
}
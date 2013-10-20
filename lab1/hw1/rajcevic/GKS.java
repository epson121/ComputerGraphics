import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class GKS extends Applet {

	private double x;
	private double y;
	private Graphics g;

	private double sx, px, sy, py;
	public int w, h;

	/*
	Konstruktorom GKS(Graphics g, double xmin, double xmax, double ymin, 
	double ymax, int xsize, int ysize) zadaje se raspon koordinata globalnog 
	koordinatnog sustava koji će biti prikazan u prozoru (appletu) 
	veličine xsize, ysize (podatak o veličini prozora nužan je da bi 
	se mogle izračunati odgovarajuće transformacije iz globalnih 
	koordinata u koordinate prozora).
	*/
	public GKS(Graphics g, double xmin, double xmax, double ymin, 
				double ymax, int xsize, int ysize) {
		this.g = g;
		this.sx = xsize / (xmax - xmin);
		this.sy = ysize / (ymax - ymin);
		this.px = -sx * xmin;
		this.py = sy * ymax;
		this.w = xsize;
		this.h = ysize;
	}

	public void postaviNa(double x, double y) {
		//transform here
		this.x = x;
		this.y = y;
	}

	public void linijaDo(double x, double y) {
		//transform before
		this.g.drawLine(transformX(this.x), transformY(this.y), 
					transformX(x), transformY(y));
	}

	public void postaviBoju(Color c) {
		this.g.setColor(c);
	}

	private int transformX(double x) {
		return (int) (this.sx * x + px);
	}

	private int transformY(double y) {
		return  (int) (-(this.sy * y) + py);
	}

}
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class GKS extends Applet {

	private double x;
	private double y;
	private Graphics g;

	private double sx, px, sy, py;
	public int w, h;
	private MT2D m;
	private double[][] matrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	private double[] vec;
	private double[] vec2;
	/**
	* Konstruktorom GKS(Graphics g, double xmin, double xmax, double ymin, 
	* double ymax, int xsize, int ysize) zadaje se raspon koordinata globalnog 
	* koordinatnog sustava koji će biti prikazan u prozoru (appletu) 
	* veličine xsize, ysize (podatak o veličini prozora nužan je da bi 
	* se mogle izračunati odgovarajuće transformacije iz globalnih 
	* koordinata u koordinate prozora).
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
		this.x = x;
		this.y = y;
	}

	public void linijaDo(double x, double y) {
		vec = new double[] {this.x, this.y, 1.0};
		vec2 = new double[] {x, y, 1.0};
		double[] r1 = mult(vec, this.matrix);
		double[] r2 = mult(vec2, this.matrix);/*
		this.g.drawLine(transformX(this.x), transformY(this.y), 
					transformX(x), transformY(y));*/
		this.g.drawLine(transformX(r1[0]), transformY(r1[1]),
						transformX(r2[0]), transformY(r2[1]));
		postaviNa(x, y);
	}

	public void postaviBoju(Color c) {
		this.g.setColor(c);
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

	public double[] mult(double[] vector, double[][] matrix) {

		double[] res = new double[vector.length];
		for (int i = 0; i < vector.length; i++) {
			for (int j = 0; j < matrix.length; j++) {
				res[i] += matrix[i][j] * vector[j];
			}
		}
		return res;
	}

	public void trans(MT2D m ) {
		this.m = m;
		double[][] temp = m.getM();
		for (int i = 0; i < temp.length; i++)  {
			for (int j = 0; j < temp.length; j++) {
				this.matrix[i][j] = temp[i][j];
			}
		}
	}



}
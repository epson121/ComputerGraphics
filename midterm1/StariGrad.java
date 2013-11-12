// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;
import java.util.Random;

public class StariGrad extends Applet {
  int xsize, ysize, iy = 0;
  int phi = 0;
  int phix = 0;
  int camHeight = 0;
  int countToSwap = 0;
  class Animacija extends Thread {
    long pauza, kraj;

    Animacija(double fps, double trajanje) {
      pauza = Math.round(1000.0 / fps);
      kraj = Math.round(trajanje * fps);
    } // Animacija

    public void run() {
      long brojac = 0;
      int korak = 2;

      while(true) {
        try {
          sleep(pauza); // pauza u milisekundama
          countToSwap += 1;
          if (countToSwap  > 80) {
            camHeight += 4;
            countToSwap = 0;
          }
        } catch (InterruptedException e) { }
          phi += 1;
          phix += 2;
          repaint();
      }
    } // run
  } // class Animacija

  public void init() {
    setBackground(Color.yellow);
    (new Animacija(30.0, 20.0)).start();
  } // init

  public void update(Graphics g) { paint(g); }

  public void paint(Graphics g) {
    xsize = getWidth();
    ysize = getHeight();
    int widthX = 5;
    int heightY = 5;
    Image slika = createImage(xsize, ysize);
    Graphics gs = slika.getGraphics();

    gs.setColor(Color.red);
    double d = 10;
    Persp p = new Persp(gs, -widthX, widthX, -heightY, heightY, d, getWidth(), getHeight());
    MT3D m = new MT3D();
    MT3D m2 = new MT3D();
    MT3D m3 = new MT3D();
    p.KSK(22 * Math.cos(Math.toRadians(phi)), 15 * Math.sin(Math.toRadians(phi)), 10, 0, 0, 0, 0, 0, 1);

    drawxyPlane(p, -widthX, widthX, -heightY, heightY);
    p.postaviBoju(Color.black);
    p.postaviBoju(Color.green);
    p.krnjiStozac(4, 2, 1, 30);
    m2.pomakni(0, 0, 1);
    p.trans(m2);
    p.postaviBoju(Color.black);
    p.valjak(2, 5, 30);
    m.pomakni(0, 0, 5);
    m.mult(m2);
    p.trans(m);
    p.postaviBoju(Color.red);
    p.stozac(2, 3, 30);
    
    m.identitet();
    m2.identitet();
    m.rotirajX(0 + phi);
    m2.pomakni(2, 0, 5);
    m2.mult(m);
    p.trans(m2);
    krilo(p);

    m.identitet();
    m2.identitet();
    m.rotirajX(90 + phi);
    m2.pomakni(2, 0, 5);
    m2.mult(m);
    p.trans(m2);
    krilo(p);

    m.identitet();
    m2.identitet();
    m.rotirajX(180 + phi);
    m2.pomakni(2, 0, 5);
    m2.mult(m);
    p.trans(m2);
    krilo(p);

    m.identitet();
    m2.identitet();
    m.rotirajX(270 + phi);
    m2.pomakni(2, 0, 5);
    m2.mult(m);
    p.trans(m2);
    krilo(p);
    /*
    m.identitet();
    m2.identitet();
    m2.rotirajY(90);
    m.rotirajX(135 + phi);
    m.mult(m2);
    p.trans(m);
    m2.pomakni(3,2, 5);
    m2.mult(m);
    p.trans(m2);
    drawxyPlane(p, -1, 1, -0.5 , 0.5);

    m.identitet();
    m2.identitet();
    m2.rotirajY(90);
    m.rotirajX(225 + phi);
    m.mult(m2);
    p.trans(m);
    m2.pomakni(3,2, 3);
    m2.mult(m);
    p.trans(m2);
    drawxyPlane(p, -1, 1, -0.5 , 0.5);

     m.identitet();
    m2.identitet();
    m2.rotirajY(90);
    m.rotirajX(315 + phi);
    m.mult(m2);
    p.trans(m);
    m2.pomakni(3,0, 3);
    m2.mult(m);
    p.trans(m2);
    drawxyPlane(p, -1, 1, -0.5 , 0.5);
    */
    //m.pomakni(double px, double py, double pz)
    g.drawImage(slika, 0, 0, null);
  }

  
  public void drawxyPlane(Persp persp, double xmin, double xmax, double ymin, double ymax) {
      double step = 0.3;
      double i;
      persp.postaviBoju(Color.blue);
      for(i = xmin; i <= xmax; i += step){
        persp.postaviNa(i, ymin, 0);
        persp.linijaDo(i, ymax, 0); 
      }

      for(i = ymin; i <= ymax; i += step){
        persp.postaviNa(xmin, i, 0);
        persp.linijaDo(xmax, i, 0);
      }

  }

  public void krilo(Persp koordinatni){
    for(double i = 0; i <= 3.02; i+=0.2){
      koordinatni.postaviNa(0,0,i);
      koordinatni.linijaDo(0,0.75,i);
    }
    for(double j = 0; j <= 0.75; j += 0.25){
      koordinatni.postaviNa(0,j,0);
      koordinatni.linijaDo(0,j,3);
    }
  }
  
}


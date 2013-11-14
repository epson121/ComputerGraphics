// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;
import java.util.Random;

public class Kolokvij extends Applet {
  int xsize, ysize, iy = 0;
  int phi = 0;
  double phix = 0;
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
          phi += 3;
          phix += 0.01;
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
    int widthX = 10;
    int heightY = 10;
    Image slika = createImage(xsize, ysize);
    Graphics gs = slika.getGraphics();

    gs.setColor(Color.red);
    double d = 10;
    Persp p = new Persp(gs, -widthX, widthX, -heightY, heightY, d, getWidth(), getHeight());
    MT3D m = new MT3D();
    MT3D m2 = new MT3D();
    MT3D m3 = new MT3D();
    MT3D m4 = new MT3D();
    //p.KSK(Math.cos(Math.toRadians(phi)) * 10, Math.sin(Math.toRadians(phi)) * 10, 10, 0, 0, 0, 0, 0, 1);
    p.KSK(10, 0, 10, 0, 0, 0, 0, 0, 1);
    //drawxyPlane(p, -widthX, widthX, -heightY, heightY);
    p.postaviBoju(Color.black);
    
    m2.rotirajZ(phi);
    p.trans(m2);
    p.valjak(2, 5, 6);


    m.rotirajX(90);
    m2.pomakni(0, 4.8, 2);
    m3.rotirajZ(phi);
    m3.mult(m2);
    m3.mult(m);
    p.trans(m3);
    p.valjak(1, 3, 6);

    m.identitet();
    m2.identitet();
    m.rotirajX(90);
    m3.rotirajZ(60 + phi);
    m2.pomakni(0, -2, 2);
    m3.mult(m2);
    m3.mult(m);
    p.trans(m3);
    p.valjak(1, 3, 6);

    m.identitet();
    m2.identitet();
    m.rotirajX(90);
    m3.rotirajZ(120 + phi);
    m2.pomakni(0, 4.7, 2);
    m3.mult(m2);
    m3.mult(m);
    p.trans(m3);
    p.valjak(1, 3, 6);

    p.postaviBoju(Color.red);
    m.identitet();
    m2.identitet();
    m.pomakni(0,0,5);
    p.trans(m);
    p.pkugla(1.5, 10, 10, 0);

    
    m.identitet();
    m2.identitet();
    m.rotirajX(180);
    p.trans(m);
    p.pkugla(1.5, 10, 10, 0);
    /*
    m.identitet();
    m2.identitet();
    m.rotirajZ(90);
    m2.pomakni(0, 0, 2);
    m2.mult(m);
    p.trans(m2);
    p.valjak(6, 2, 15);
    
    m.identitet();
    m2.identitet();
    m.rotirajZ(90);
    m2.pomakni(0, 0, 2);
    m2.mult(m);
    p.trans(m2);
    p.valjak(5, 2, 15);
    */

    

    
    //m.pomakni(double px, double py, double pz)
    g.drawImage(slika, 0, 0, null);
  }

  
  public void drawxyPlane(Persp persp, int xmin, int xmax, int ymin, int ymax) {
      double step = 0.3;
      double i;
      persp.postaviBoju(Color.green);
      for(i = xmin; i <= xmax; i += step){
        persp.postaviNa(i, ymin, 0);
        persp.linijaDo(i, ymax, 0); 
      }

      for(i = ymin; i <= ymax; i += step){
        persp.postaviNa(xmin, i, 0);
        persp.linijaDo(xmax, i, 0);
      }

  }

 
   public void cube(Persp o, double a) {
    o.postaviNa(0, 0, 0);
    o.linijaDo(a, 0, 0);
    o.linijaDo(a, 0, a);
    o.linijaDo(0, 0, a);
    o.linijaDo(0, 0, 0); 
    
    o.linijaDo(0, a, 0);
    o.linijaDo(0, a, a);
    o.linijaDo(0, 0, a);
    o.linijaDo(0, 0, 0);
    
    o.linijaDo(0, a, 0);
    o.linijaDo(a, a, 0);
    o.linijaDo(a, a, a);
    o.linijaDo(0, a, a);
    o.linijaDo(a, a, a);

    o.linijaDo(a, 0, a);
    o.linijaDo(a, 0, 0);
    o.linijaDo(a, a, 0);
  }

}


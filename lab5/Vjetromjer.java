// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;
import java.util.Random;

public class Vjetromjer extends Applet {
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
          phi += 3;
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
    p.KSK(12, 12, 10, 0, 0, 0, 0, 0, 1);

    drawxyPlane(p, -widthX, widthX, -heightY, heightY);
    p.postaviBoju(Color.black);
    int stozacVisina = 5;


    // postolje i valjak na vrhu    
    p.stozac(2, stozacVisina, 20);
    m.pomakni(0, 0, stozacVisina-1);
    p.trans(m);
    m3.rotirajZ(phi);
    m3.mult(m);
    p.trans(m3);
    p.valjak(0.6, 1, 10);
    m2.rotirajY(90);
    m2.mult(m3);
    p.trans(m2);
    m.pomakni(0, 0, stozacVisina);
    m.mult(m2);
    p.trans(m2);
    
    // ruka 1
    m.identitet();
    m2.identitet();
    m2.rotirajX(90);
    m.pomakni(0, 4.5, 0);
    m2.mult(m);
    p.trans(m2);
    m3.rotirajZ(phi);
    m3.mult(m2);
    p.trans(m3);
    p.valjak(0.4, 4, 6);

    // polukugla 1
    m.identitet();
    m2.identitet();
    m.rotirajX(-90);
    m2.rotirajY(-90);
    m2.mult(m);
    p.trans(m2);
    m.pomakni(0, -4.8, 4.5);
    m.mult(m2);
    p.trans(m);
    m3.rotirajZ(phi);
    m3.mult(m);
    p.trans(m3);
    p.polukugla(0.8, 10, 10);
   
    // ruka 2
    m.identitet();
    m2.identitet();
    m2.rotirajX(90);
    m.rotirajZ(120);
    m.mult(m2);
    m2.pomakni(0, 0, 4.5);
    m2.mult(m);
    p.trans(m2);
    m3.rotirajZ(phi);
    m3.mult(m2);
    p.trans(m3);
    p.valjak(0.4, 4, 6);
    
    // polukugla 2
    m.identitet();
    m2.identitet();
    m.rotirajX(-90);
    m2.rotirajY(-90);
    m2.mult(m);
    p.trans(m2);
    m.rotirajZ(120);
    m.mult(m2);
    p.trans(m);
    m2.pomakni(3.9, 2.6, 4.5);
    m2.mult(m);
    p.trans(m2);
    m3.rotirajZ(phi);
    m3.mult(m2);
    p.trans(m3);
    p.polukugla(0.8, 10, 10);

    // ruka 3
    m.identitet();
    m2.identitet();
    m2.rotirajX(90);
    m.rotirajZ(240);
    m.mult(m2);
    m2.pomakni(0, 0, 4.5);
    m2.mult(m);
    p.trans(m2);
    m3.rotirajZ(phi);
    m3.mult(m2);
    p.trans(m3);
    p.valjak(0.4, 4, 6);

    // polukugla 3
    m.identitet();
    m2.identitet();
    m.rotirajX(-90);
    m2.rotirajY(-90);
    m2.mult(m);
    p.trans(m2);
    m.rotirajZ(240);
    m.mult(m2);
    p.trans(m);
    m2.pomakni(-3.9, 2.6, 4.5);
    m2.mult(m);
    p.trans(m2);
    m3.rotirajZ(phi);
    m3.mult(m2);
    p.trans(m3);
    p.polukugla(0.8, 10, 10);
    
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


  /*public void drawxyPlane(Persp o, int w, int h) {
    double i = -w;
    double j = -h;
    double step = 0.2;
    w = w*2;
    h = h*2;
    o.postaviNa(-w, -h, 0);
    o.postaviBoju(Color.green);
    while (i < w) {
      o.linijaDo(w, i, 0);
      o.postaviNa(-w, i+step, 0); 
      i += step;
    }
    
    o.postaviNa(0, 0, 0);
    while(j < h) {
      o.linijaDo(j, h, 0);
      o.postaviNa(j+step, -h, 0);
      j += step;
    }
  }*/
  
}


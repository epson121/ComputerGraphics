// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;
import java.util.Random;

public class FCamera extends Applet {
  int xsize, ysize, iy = 0;
  int phi = 0;
  int phix = 2, phiy=2, phiz=2;
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
          if (countToSwap  > 160) {
            camHeight += 1;
            countToSwap = 0;
          }
        } catch (InterruptedException e) { }
          phix += 2;
          phiy += 2;
          phiz += 2;
          phi += 5;
          repaint();
      }
    } // run
  } // class Animacija

  public void init() {
    setBackground(Color.yellow);
    (new Animacija(25.0, 20.0)).start();
  } // init

  public void update(Graphics g) { paint(g); }

  public void paint(Graphics g) {
    xsize = getWidth();
    ysize = getHeight();
    int widthX = 15;
    int heightY = 15;
    Image slika = createImage(xsize, ysize);
    Graphics gs = slika.getGraphics();

    gs.setColor(Color.red);

    Ortho o = new Ortho(gs, -widthX, widthX, -heightY, heightY, getWidth(), getHeight());
    MT3D m = new MT3D();
    MT3D m2 = new MT3D();
    o.KSK(Math.cos(Math.toRadians(phi)), Math.sin(Math.toRadians(phi)), camHeight, 0, 0, 0, 0, 0, 1);

    o.postaviNa(-widthX, 0, 0);
    // x axis
    /*o.postaviBoju(Color.green);
    o.linijaDo(widthX+1, 0, 0);
    o.postaviNa(0, -heightY, 0);
    // y axis
    o.postaviBoju(Color.blue);
    o.linijaDo(0, heightY+1, 0);
    o.postaviNa(0, 0, -heightY);
    //z axis
    o.postaviBoju(Color.red);
    o.linijaDo(0, 0, heightY);
    o.postaviBoju(Color.black);
  */
    m.pomakni(-3.25, -3.25, 0);
    o.trans(m);
    drawxyPlane(o, widthX, heightY);
    o.postaviBoju(Color.black);
    m2.pomakni(2, 2, 0);
    m2.mult(m);
    o.trans(m2);
    cube(o, 1);
    m.pomakni(0, 0, 1);
    m.mult(m2);
    o.trans(m);
    cube(o, 1);
    m2.pomakni(0, 0, 1);
    m2.mult(m);
    o.trans(m2);
    cube(o, 1);
    m.pomakni(0, 1, 0);
    m.mult(m2);
    o.trans(m);
    cube(o, 1);
    m2.pomakni(0, -1, 1);
    m2.mult(m);
    o.trans(m2);
    cube(o, 1);
    m.pomakni(0, 0, 1);
    m.mult(m2);
    o.trans(m);
    cube(o, 1);
    m2.pomakni(0, 1, 0);
    m2.mult(m);
    o.trans(m2);
    cube(o, 1);
    m.pomakni(0, 1, 0);
    m.mult(m2);
    o.trans(m);
    cube(o, 1);
    //m.pomakni(double px, double py, double pz)
    g.drawImage(slika, 0, 0, null);
  }

  public void cube(Ortho o) {
    o.postaviNa(-1, -1, -1);
    o.linijaDo(1, -1, -1);
    o.linijaDo(1,1,-1);
    o.linijaDo(-1, 1, -1);
    o.linijaDo(-1, -1, -1); 
    
    o.postaviNa(1, -1, 1);
    o.linijaDo(1, -1, 1);
    o.linijaDo(1, 1, 1);
    o.linijaDo(-1, 1, 1);
    o.linijaDo(-1, -1, 1);
    o.linijaDo(1, -1, 1);

    o.linijaDo(1, -1, -1);
    o.linijaDo(1, 1, -1);
    o.linijaDo(1, 1, 1);
    o.linijaDo(1, -1, 1);

    o.linijaDo(-1, -1, 1);
    o.linijaDo(-1, 1, 1);
    o.linijaDo(-1, 1, -1);
    o.linijaDo(-1, -1, -1);
    o.linijaDo(-1, -1, 1) ;
  }

   public void cube(Ortho o, int a) {
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

  public void drawxyPlane(Ortho o, int w, int h) {
    double i = 0;
    double j = 0;
    double step = 0.2;
    o.postaviNa(0, 0, 0);
    o.postaviBoju(Color.green);
    while (i < w/2) {
      o.linijaDo(w/2, i, 0);
      o.postaviNa(0, i+step, 0); 
      i += step;
    }
    
    o.postaviNa(0, 0, 0);
    while(j < h/2) {
      o.linijaDo(j, h/2, 0);
      o.postaviNa(j+step, 0, 0);
      j += step;
    }
  }
  
}


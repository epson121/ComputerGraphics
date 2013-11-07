// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;
import java.util.Random;

public class Valjak extends Applet {
  int xsize, ysize, iy = 0;
  int phi = 0;
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
            camHeight += 2;
            countToSwap = 0;
          }
        } catch (InterruptedException e) { }
          phi += 3;
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
    Persp o = new Persp(gs, -widthX, widthX, -heightY, heightY, d, getWidth(), getHeight());
    MT3D m = new MT3D();
    MT3D m2 = new MT3D();
    //o.KSK(cx, cy, camHeight, 0, 0, 0, 0, 0, 1);
    o.KSK(10, 10, 10, 0, 0, 0, 0, 0, 1);

    o.postaviNa(0, 0, 0);
    o.valjak(5, 5, 20);

    /*
    o.postaviNa(-widthX, 0, 0);
    
    m.pomakni(-3.25, -3.25, 0);
    o.trans(m);
    drawxyPlane(o, widthX, heightY);
    o.postaviBoju(Color.black);
    m2.pomakni(6, 6, 0);
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
    */
    //m.pomakni(double px, double py, double pz)
    g.drawImage(slika, 0, 0, null);
  }

   public void cube(Persp o, int a) {
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

  public void drawxyPlane(Persp o, int w, int h) {
    double i = 0;
    double j = 0;
    double step = 0.2;
    w = w*2;
    h = h*2;
    o.postaviNa(0, 0, 0);
    o.postaviBoju(Color.green);
    while (i < w) {
      o.linijaDo(w, i, 0);
      o.postaviNa(0, i+step, 0); 
      i += step;
    }
    
    o.postaviNa(0, 0, 0);
    while(j < h) {
      o.linijaDo(j, h, 0);
      o.postaviNa(j+step, 0, 0);
      j += step;
    }
  }
  
}


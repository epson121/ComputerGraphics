// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;
import java.util.Random;

public class FOI3D extends Applet {
  int xsize, ysize, iy = 0;
  int phi = 0;
  double phix = 0;
  int camHeight = 0;
  int countToSwap = 0;
  int splitter = 400;
  boolean up = true;
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

          if (up) {
            splitter += 30;
          } else {
            splitter -= 30;
          }

          if (splitter > 1200) {
             up = false;
          } 
          if (splitter < 350) {
            up = true;
          }
            
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
    Persp o = new Persp(gs, -widthX, widthX, -heightY, heightY, d, getWidth(), getHeight());
    MT3D m = new MT3D();
    MT3D m2 = new MT3D();
    MT3D m3 = new MT3D();
    MT3D m4 = new MT3D();
    o.KSK(Math.cos(Math.toRadians(phi)) * 10, Math.sin(Math.toRadians(phi)) * 10, 10, 0, 0, 0, 0, 0, 1);
    //o.KSK(10, 0, 10, 0, 0, 0, 0, 0, 1);
    drawxyPlane(o, -widthX, widthX, -heightY, heightY);
    o.postaviBoju(Color.black);
    

    o.krnjiStozac(8, 6, 1, 20);
    m.pomakni(-6, -11, 1);
    o.trans(m);
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

    m.identitet();
    m2.identitet();
    m.pomakni(0, 0, 3);
    o.trans(m);
    o.elipsoid (1, 2, 30, 30);


    m.identitet();
    m2.identitet();
    m.pomakni(0, 3, 1);
    o.trans(m);
    spirala(o, 1, 1, 0.01, splitter);
    
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

  public void spirala(Persp o, double a, double b, double step, int s) {
    double phi;
    double x, y;
    double startZ = 0;
    o.postaviNa(a * Math.cos(0), b * Math.sin(0), startZ);
    for(phi = 0; phi <= 8.0 * Math.PI + step; phi += 0.01, startZ += 0.5) {
      x = a * Math.cos(phi);
      y = b * Math.sin(phi);
      o.linijaDo(x, y, startZ/s);
    }
    MT3D m = new MT3D();
    m.pomakni(0, 3, 1 + startZ/s);
    o.trans(m);
    o.kugla(1, 10, 10);
  }

}


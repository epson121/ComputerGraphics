// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;
import java.util.Random;

public class Avion extends Applet {
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
    MT3D m4 = new MT3D();
    p.KSK(Math.cos(Math.toRadians(phi)) * 10, Math.sin(Math.toRadians(phi)) * 10, 3, 0, 0, 0, 0, 0, 1);
    //p.KSK(10, 0, 10, 0, 0, 0, 0, 0, 1);
    drawxyPlane(p, -widthX, widthX, -heightY, heightY);
    p.postaviBoju(Color.black);
    
    //glavno krilo
    m.rotirajY(90);
    m2.pomakni(-0.9, -4, 1);
    m2.mult(m);
    p.trans(m2);
    krilo(p, 4, 20, 8, 5);

    // trup aviona
    m.identitet();
    m.rotirajY(90);
    p.trans(m);
    p.stozac(1, 2, 20);

    m.identitet();
    m.rotirajY(-90);
    p.trans(m);
    p.stozac(1, 4, 20);
    
    m.rotirajY(90);
    m2.pomakni(-4.5, -2, 0);
    m2.mult(m);
    p.trans(m2);
    krilo(p, 4, 10, 4, 5);


    m.rotirajZ(90);
    m2.pomakni(-3.5, 0, 0);
    m2.mult(m);
    p.trans(m2);
    krilo(p, 4, 10, 1, 5);

    m.rotirajZ(90);
    m2.pomakni(-3.5, 0, 0);
    m2.mult(m);
    p.trans(m2);
    krilo(p, 4, 10, 1, 5);

    m.identitet();
    m2.identitet();
    m2.rotirajY(-90);
    m.pomakni(0, 2, 0.90);
    m.mult(m2);
    p.trans(m);
    p.stozac(0.2, 1, 20);

   // lijevi propeler 1

    m.identitet();
    m2.identitet();
    m.pomakni(0, -1.6, 0.9);
    m2.rotirajY(90);
    m.mult(m2);
    m2.rotirajX(phi);
    m2.mult(m);
    p.trans(m2);
    elipse(p, 0.1, 0.5, 0.01);

    m.identitet();
    m2.identitet();
    m2.rotirajY(-90);
    m.pomakni(0, -2, 0.90);
    m.mult(m2);
    p.trans(m);
    p.stozac(0.2, 1, 20);

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

  public void krilo2(Persp koordinatni){
    for(double i = 0; i <= 3.02; i+=0.2){
      koordinatni.postaviNa(0,0,i);
      koordinatni.linijaDo(0,0.75,i);
    }
    for(double j = 0; j <= 0.75; j += 0.25){
      koordinatni.postaviNa(0,j,0);
      koordinatni.linijaDo(0,j,3);
    }
  }

  public void elipse(Persp p, double a, double b, double step) {
    double phi;
    double x, y;
    p.postaviNa(a * Math.cos(0), b * Math.sin(0), 0);
    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
      x = a * Math.cos(phi);
      y = b * Math.sin(phi);
      p.linijaDo(x, y, 0);
    }
  }

  // s -> size (width)
  // h coefficient -> bigger - smaller cubes
  public void krilo(Persp koordinatni, int r, int c, double s, double h){
    for(double i = 0; i <= r; i++){
      koordinatni.postaviNa(0, 0, i/h);
      koordinatni.linijaDo(0, s, i/h);
    }
    
    double temp = r/h;
    for(double j = 0; j <= c; j++){
      koordinatni.postaviNa(0,j*(s / c), 0);
      koordinatni.linijaDo(0,j * (s/c), temp);
    }
  }


}


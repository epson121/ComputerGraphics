// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;
import java.util.Random;

public class FCamera extends Applet {
  int xsize, ysize, iy = 0;
  int phi = 2;
  int phix = 2, phiy=2, phiz=2;
  double cx = 10, cy = 0, cz = 0;
  boolean reverseX = false;
  boolean reverseY = false;
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
        } catch (InterruptedException e) { }
          phix += 2;
          phiy += 2;
          phiz += 2;
          int xLim = 30;
          int yLim = 30;
          double speed = 0.5;
          if (cx > xLim) {
            reverseX = true;
          }
          if (cx < -xLim) {
            reverseX = false;
          }

          if (cy > yLim) {
            reverseY = true;
          }
          if (cy < -yLim) {
            reverseY = false;
          }

          if (reverseX) {
            cx -= speed;
          } else {
            cx += speed;
          }
          
          if (reverseY) {
            cy -= speed;
          } else {
            cy += speed;
          }
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
    o.KSK(cx, cy, 15, 0, 0, 0, 3, 3, 3);
    o.postaviNa(-widthX, 0, 0);
    // x axis
    o.postaviBoju(Color.green);
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
    m.rotirajZ(phix);
    /*m2.rotirajY(phix);
    m2.mult(m);
    m.rotirajY(phiy);
    m.mult(m2);
    
    m2.rotirajZ(phiz);
    m2.mult(m);
    o.trans(m2);
    o.postaviBoju(Color.black);   
    //m2.rotirajZ(45);
    //m.rotirajY(-30);
    //m.mult(m2);
    //m2.rotirajZ(30);
    //m2.rotiraj(2, -5, 2, -3, 5, -3,  phi);
    //m2.mult(m);
    //o.trans(m2);*/
    cube(o);
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
  
}


// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;
import java.util.Random;

public class CubeRotationOverLine extends Applet {
  int xsize, ysize, iy = 0;
  int phi = 2;

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

    Image slika = createImage(xsize, ysize);
    Graphics gs = slika.getGraphics();

    gs.setColor(Color.red);

    Ortho o = new Ortho(gs, -15, 15, -15, 15, getWidth(), getHeight());
    MT3D m = new MT3D();
    MT3D m2 = new MT3D();

    o.postaviNa(-10, 19, 5);
    o.linijaDo(10, -21, 5);
    o.postaviBoju(Color.black);
        
    m2.rotirajZ(-45);
    m.rotirajY(30);
    m.mult(m2);
    //m2.rotirajZ(30);
    m2.rotiraj(-3, 5, -3, 2, -5, 2, phi);
    m2.mult(m);
    o.trans(m2);
    cube(o, 2);
    g.drawImage(slika, 0, 0, null);
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

}


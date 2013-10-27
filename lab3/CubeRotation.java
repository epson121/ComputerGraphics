// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;
import java.util.Random;

public class CubeRotation extends Applet {
  int xsize, ysize, iy = 0;
  int phix = 2;
  int phiy = 2;
  int phiz = 2;

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
        phix += 5;
        phiy += 5;
        phiz += 3;
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

    Ortho o = new Ortho(gs, -4, 4, -4, 4, getWidth(), getHeight());
    MT3D m = new MT3D();
    MT3D m2 = new MT3D();
    o.postaviBoju(Color.red);
    m.pomakni(0.5, 0.2, 0.7);
    m2.rotirajX(phix);
    m2.mult(m);
    m.rotirajY(phiy);
    m.mult(m2);
    
    m2.rotirajZ(phiz);
    m2.mult(m);
    o.trans(m2);
    o.postaviBoju(Color.black);
    cube(o);
    //o.trans(m);
    //cube(o);
    g.drawImage(slika, 0, 0, null);
  } // paint

  public void cube(Ortho o) {
    o.postaviNa(0, 0, 0);
    o.linijaDo(1, 0, 0);
    o.linijaDo(1, 0, 1);
    o.linijaDo(0, 0, 1);
    o.linijaDo(0, 0, 0); 
    
    o.linijaDo(0, 1, 0);
    o.linijaDo(0, 1, 1);
    o.linijaDo(0, 0, 1);
    o.linijaDo(0, 0, 0);
    
    o.linijaDo(0, 1, 0);
    o.linijaDo(1, 1, 0);
    o.linijaDo(1, 1, 1);
    o.linijaDo(0, 1, 1);
    o.linijaDo(1, 1, 1);

    o.linijaDo(1, 0, 1);
    o.linijaDo(1, 0, 0);
    o.linijaDo(1, 1, 0);
    //o.linijaDo(1, 0, 0);
  }

} // class JAnimacija2


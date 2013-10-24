// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;

public class Ventilator extends Applet {
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
        phi += 10;
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

    Image slika = createImage(xsize, ysize);
    Graphics gs = slika.getGraphics();

    gs.setColor(Color.red);

    GKS gks = new GKS(gs, -10, 10, -10, 10, xsize, ysize);
    MT2D m = new MT2D();
    MT2D m2 = new MT2D();

    elipse(gks, 1, 1, 0.01);
    m2.pomakni(5, 0);
    m.rotiraj(phi);
    m.mult(m2);
    gks.trans(m);
    elipse(gks, 4, 0.5, 0.01);
    m2.rotiraj(120);
    m2.mult(m);
    gks.trans(m2);
    elipse(gks, 4, 0.5, 0.01);
    m.rotiraj(120);
    m.mult(m2);
    gks.trans(m);
    elipse(gks, 4, 0.5, 0.01);
    
    
    g.drawImage(slika, 0, 0, null);
  } // paint

  public void elipse(GKS gks, double a, double b, double step) {
    double phi;
    double x, y;
    gks.postaviNa(a * Math.cos(0), b * Math.sin(0));
    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
      x = a * Math.cos(phi);
      y = b * Math.sin(phi);
      gks.linijaDo(x, y);
    }
  }

} // class JAnimacija2


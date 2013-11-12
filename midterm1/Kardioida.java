// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;

public class Kardioida extends Applet {
  int xsize, ysize, iy = 0;
  double phi = 0;
  //double i = 0;
  double ox = 1.5;
  double oy = 0;
  double total = 0;
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
        if (phi < 2 * Math.PI){
          phi += 0.03;
        }
        if (total < 2 * Math.PI) {
          total += 0.03;
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

    Image slika = createImage(xsize, ysize);
    Graphics gs = slika.getGraphics();

    

    GKS gks = new GKS(gs, -5, 5, -5, 5, xsize, ysize);
    MT2D m = new MT2D();
    MT2D m2 = new MT2D();

    //koordinatne osi
    gs.setColor(Color.black);
    gks.postaviNa(-5, 0);
    gks.linijaDo(5, 0);
    gks.postaviNa(0, -5);
    gks.linijaDo(0, 5);
    
    gks.postaviBoju(Color.blue);
    elipse(gks, 1.5, 1.5, 0.2);

    gks.postaviNa(ox, oy);
    //kardioida
    for (double i = 0; i < total; i += 0.01) {
    gks.linijaDo(1.5 * (2 * Math.cos(i) - Math.cos(2 * i)), 
                   1.5 * (2 * Math.sin(i) - Math.sin(2 * i)));
    }
    //koordinate za malu kruznicu
    double x_help = 1.5 * (2 * Math.cos(total) - Math.cos(2 * total));
    double y_help = 1.5 * (2 * Math.sin(total) - Math.sin(2 * total));
    m2.pomakni(x_help, y_help);
    gks.trans(m2);
    elipse(gks, 0.3, 0.3, 0.2);
    //velika kruznica
    m.identitet();
    m.pomakni(3 * Math.cos(phi), 3 * Math.sin(phi));
    gks.trans(m);
    elipse(gks, 1.5, 1.5, 0.2);
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


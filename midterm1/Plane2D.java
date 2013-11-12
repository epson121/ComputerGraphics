// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;

public class Plane2D extends Applet {
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

    Image slika = createImage(xsize, ysize);
    Graphics gs = slika.getGraphics();

    

    GKS gks = new GKS(gs, -10, 10, -10, 10, xsize, ysize);
    MT2D m = new MT2D();
    MT2D m2 = new MT2D();

    //koordinatne osi
    gs.setColor(Color.black);

    gks.postaviNa(-7, 3);
    gks.linijaDo(7, 3);
    gks.postaviNa(0, 3);
    gks.linijaDo(0, 6);

    //trup
    elipse(gks, 3, 3, 0.02);
    double prozor = 180.0 / 8;
    double pomoc = (Math.PI * prozor) / 180;
    gks.postaviNa(2 * Math.cos(pomoc), 2 * Math.sin(pomoc));
    
    for(double go = pomoc; go <= (7 * pomoc); go += pomoc){
      double x = 2 * Math.cos(go);
      double y = 2 * Math.sin(go);
      gks.linijaDo(x,y);
    }

    for(double go = pomoc; go <= (7 * pomoc); go += pomoc){
      gks.postaviNa(0,0);
      double x = 2 * Math.cos(go);
      double y = 2 * Math.sin(go);
      gks.linijaDo(x,y);
    }
    

    //lijevi motor
    m.pomakni(-5, 1);
    gks.trans(m);
    elipse(gks, 1, 1, 0.02);

    m.pomakni(-5, 1);
    gks.trans(m);
    elipse(gks, 0.5, 0.5, 0.02);

    // lijevi propeler 1
    m.identitet();
    m2.identitet();
    m2.pomakni(2, 0);
    m.rotiraj(0 + phi);
    m.mult(m2);
    m2.pomakni(-5, 1);
    m2.mult(m);
    gks.trans(m2);
    elipse(gks, 2, 0.5, 0.01);

    m.identitet();
    m2.identitet();
    m2.pomakni(2, 0);
    m.rotiraj(120 + phi);
    m.mult(m2);
    m2.pomakni(-5, 1);
    m2.mult(m);
    gks.trans(m2);
    elipse(gks, 2, 0.5, 0.01);

    m.identitet();
    m2.identitet();
    m2.pomakni(2, 0);
    m.rotiraj(240 + phi);
    m.mult(m2);
    m2.pomakni(-5, 1);
    m2.mult(m);
    gks.trans(m2);
    elipse(gks, 2, 0.5, 0.01);

     //desni motor
    m.pomakni(5, 1);
    gks.trans(m);
    elipse(gks, 1, 1, 0.02);

    m.pomakni(5, 1);
    gks.trans(m);
    elipse(gks, 0.5, 0.5, 0.02);
    
    // lijevi propeler 1
    m.identitet();
    m2.identitet();
    m2.pomakni(-2, 0);
    m.rotiraj(0 + phi);
    m.mult(m2);
    m2.pomakni(5, 1);
    m2.mult(m);
    gks.trans(m2);
    elipse(gks, 2, 0.5, 0.01);

    m.identitet();
    m2.identitet();
    m2.pomakni(-2, 0);
    m.rotiraj(120 + phi);
    m.mult(m2);
    m2.pomakni(5, 1);
    m2.mult(m);
    gks.trans(m2);
    elipse(gks, 2, 0.5, 0.01);

    m.identitet();
    m2.identitet();
    m2.pomakni(-2, 0);
    m.rotiraj(240 + phi);
    m.mult(m2);
    m2.pomakni(5, 1);
    m2.mult(m);
    gks.trans(m2);
    elipse(gks, 2, 0.5, 0.01);


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

   public void poluelipsa(GKS koordinatni, double a, double b, double step){
    koordinatni.postaviNa(a * Math.cos(Math.PI / 2), b* Math.sin(Math.PI / 2));
    
    for(double phi = (Math.PI / 2); phi <= (Math.PI * 3/2) + step; phi += step){
      double x = a * Math.cos(phi);
      double y = b * Math.sin(phi);
      koordinatni.linijaDo(x,y);
    }
  }//poluelipsa

} // class JAnimacija2


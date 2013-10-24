// indirektno iscrtavanje

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;

public class JAnimacija2 extends Applet {
  int xsize, ysize, iy = 0;

  class Animacija extends Thread {
    long pauza, kraj;

    Animacija(double fps, double trajanje) {
    // fps - broj sličica u sekundi
    // trajanje - trajanje u sekundama

      // pauza između sličica u milisekundama
      pauza = Math.round(1000.0 / fps);

      // poslije koliko koraka animacija završava
      kraj = Math.round(trajanje * fps);
    } // Animacija

    public void run() {
      long brojac = 0;
      int korak = 2;

      while(brojac++ < kraj) {
        try {
          sleep(pauza); // pauza u milisekundama
        } catch (InterruptedException e) { }
        if(iy >= ysize) korak = -2;
        if(iy < 0) korak = 2;
        iy += korak; // pomakni po y koordinati
        repaint(); // traži ponovno iscrtavanje
      }
    } // run
  } // class Animacija

  public void init() {
    setBackground(Color.yellow);
    // 30 sličica u sekundi u trajanju 20 sekundi
    (new Animacija(30.0, 20.0)).start();
  } // init

  public void update(Graphics g) { paint(g); }

  public void paint(Graphics g) {
    xsize = getWidth();
    ysize = getHeight();

    Image slika = createImage(xsize, ysize);
    Graphics gs = slika.getGraphics();

    gs.setColor(Color.red);
    gs.drawLine(0, iy, xsize, iy);

    g.drawImage(slika, 0, 0, null);
  } // paint

} // class JAnimacija2


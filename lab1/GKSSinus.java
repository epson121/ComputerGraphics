
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class GKSSinus extends Applet {

  @Override
  public void init() { 
    setBackground(Color.yellow);   
  }

  @Override
  public void paint(Graphics g) {
    GKS gks = new GKS(g, 0, 6.28, -1, 1, 640, 400);
    gks.postaviBoju(Color.black);
    
    //koordinatne osi
    gks.postaviNa(0, 0);
    gks.linijaDo(gks.w, 0);

    gks.postaviBoju(Color.red);
    double i = 0;
    double jump = 0.1;
    do {
      double y1 = Math.sin(i);
      double y2 = Math.sin(i + jump);
      gks.postaviNa(i, y1);
      gks.linijaDo(i + jump, y2);
      i += jump;
    } while (i <= gks.w);
    
  }
}
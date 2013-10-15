
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class GKSParabola extends Applet {

  @Override
  public void init() { 
    setBackground(Color.yellow);   
  }

  @Override
  public void paint(Graphics g) {
    GKS gks = new GKS(g, -5, 5, -5, 5, getWidth(), getHeight());
    gks.postaviBoju(Color.black);
    
    // draw axis
    gks.postaviNa(-5, 0);
    gks.linijaDo(5, 0);
    gks.postaviNa(0, 5);
    gks.linijaDo(0, -5);

    gks.postaviBoju(Color.red);
    double i = -5;
    double jump = 0.1;
    do {
      double y1 = 0.5 * i*i - 3;
      double y2 = 0.5 * (i+jump)*(i+jump) - 3;
      gks.postaviNa(i, y1);
      gks.linijaDo(i + jump, y2);
      i += jump;
    } while (i <= 5);
    
  }
}
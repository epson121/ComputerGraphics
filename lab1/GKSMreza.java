import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class GKSMreza extends Applet {

  @Override
  public void init() {   
    setBackground(Color.yellow); 
  }

  @Override
  public void paint(Graphics g) {
    GKS gks = new GKS(g, 0, 10, 0, 10, 500, 500);
    gks.postaviBoju(Color.RED);
    
    for (int i = 0; i <= 10; i+=1) {
            gks.postaviNa(i, 0);
            gks.linijaDo(i, gks.w);
    }
    
    for (int i = 0; i <= 10; i+=1) {
            gks.postaviNa(0, i);
            gks.linijaDo(gks.w, i);
    }
    
  }
}
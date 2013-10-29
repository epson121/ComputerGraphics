
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class Cube1 extends Applet {

  @Override
  public void init() { 
    setBackground(Color.yellow);   
  }

  @Override
  public void paint(Graphics g) {
    Ortho o = new Ortho(g, -2, 2, -2, 2, getWidth(), getHeight());
    MT3D m = new MT3D();
    MT3D m2 = new MT3D();
    o.postaviBoju(Color.red);
    //cube(o);
    /*m.rotirajX(30);
    o.trans(m);
    cube(o);  
    m2.rotirajY(30);
    //m2.mult(m);
    o.trans(m2);
    o.postaviBoju(Color.green);
    cube(o);
    m.rotirajZ(30);
    //m.mult(m2);
    o.trans(m);
    o.postaviBoju(Color.blue);
    cube(o);*/
    //m2.rotirajZ(30);
    m.rotirajZ(30);
    //m.mult(m2);
    /*m2.rotirajZ(30);
    m2.mult(m);*/
    o.trans(m);
    o.postaviBoju(Color.black);
    cube(o);
  
    
  }

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
    o.linijaDo(1, 0, 0);
  }

  
}
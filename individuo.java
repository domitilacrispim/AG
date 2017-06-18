/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ag;

import java.util.Comparator;
import java.util.Vector;

/**
 *
 * @author domiflorzinha
 */
public class individuo implements Comparable<individuo> {
   public Vector <Integer> ser = new Vector();
   public double nota;
   public Vector <Integer> restante = new Vector();
    public Vector CriaIndividuo (){
        int i, j=0;  
        nota=-1; // System.out.print("Digimon");
        while (true){
            i=((int)(Math.random()*10));
            Integer r =i;  
            if(!ser.contains(r)){
                j++; 
                ser.add(i);
            }
            if(j==8) break;// System.out.print("Digimon");
        }
        
       // this.Resto();
       //System.out.print("2!\n");
        return ser;
    }
    public double AvaliaIndividuo(){
        double y,q,p;
        y=ser.get(7)+10*ser.get(1)+100*ser.get(2)+1000*ser.get(5)+10000*ser.get(4);
        p=ser.get(3)+ser.get(2)*10+ser.get(1)*100+ser.get(0)*1000;
        q=ser.get(1)+ser.get(6)*10+ser.get(5)*100+ser.get(4)*1000;
        this.nota=(y-(p+q)); 
        return (y-(p+q));
    }
 /*   public  void Resto (){
        for (int i=0; i<10; i++){
            restante.add(i);
        } 
        for (int i=0; i<10; i++){
            if (ser.contains(i)){
                restante.remove(i);
            }
            System.out.print("2!\n");
        }
    }*/
    
    public int verifica (){
    Vector a1 = new Vector ();
    int u=0;
    while(u<ser.size()){
        if(a1.contains(ser.get(u))){
            return u;
        }
        a1.add(ser.get(u));
        u++;
    }
    return -1;
  }
    public int compareTo (individuo carro){
        if(carro.nota>this.nota){
            return 1;
        }
        return -1;
    }
}

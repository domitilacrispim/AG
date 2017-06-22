           /*
            * To change this license header, choose License Headers in Project Properties.
            * To change this template file, choose Tools | Templates
            * and open the template in the editor.
            */
           package ag;

           import java.util.ArrayList;
           import java.util.Collections;
           import java.util.List;
           import java.util.Vector;

           /**
            *
            * @author domiflorzinha
            */
           public class metodos    {
                      public List <individuo> populacao = new ArrayList<individuo> ();
                      public void Criapop (Integer f){
                          int t=0;// System.out.print("1!\n");
                          while(true){
                              individuo o = new individuo();
                              o.ser=o.CriaIndividuo(); //System.out.print("2!\n");
                              this.populacao.add(o);
                              t++; 
                              if(t==f) break;
                          }
                      }
                      public Boolean AvaliaPop (){
                           double x; Boolean y=false;
                          Integer p=0, o =  populacao.size();
                           while (true){
                               x=populacao.get(p).nota;
                               if(populacao.get(p).nota == -1){
                                   x=populacao.get(p).AvaliaIndividuo();
                                   populacao.get(p).nota=x; 
                               }
                               if(x==0) y=true;
                               p++;   
                                if(p==o) break;

                           }
                           return y;
                      }
                   public void Cruzamento (){
                       int p = populacao.size(), o, i, a;
                       individuo mae = new individuo ();
                       individuo pai = new individuo ();
                       o=((int)(Math.random()*p));
                       a=((int)(Math.random()*p));
                       i=((int)(Math.random()*p));
                       if ( populacao.get(o).nota >= populacao.get(a).nota &&  populacao.get(o).nota >= populacao.get(i).nota){
                               mae=populacao.get(o);
                       }
                       if ( populacao.get(a).nota >= populacao.get(o).nota &&  populacao.get(a).nota >= populacao.get(i).nota){
                               mae=populacao.get(a);
                       }
                       if ( populacao.get(i).nota >= populacao.get(o).nota &&  populacao.get(a).nota <= populacao.get(i).nota){
                               mae=populacao.get(i);
                       }
                       while(true){
                           o=((int)(Math.random()*p));
                           a=((int)(Math.random()*p));
                           i=((int)(Math.random()*p));
                           if ( populacao.get(o).nota >= populacao.get(a).nota &&  populacao.get(o).nota >= populacao.get(i).nota){
                               pai=populacao.get(o);
                           }
                           if ( populacao.get(a).nota >= populacao.get(o).nota &&  populacao.get(a).nota >= populacao.get(i).nota){
                               pai=populacao.get(a);
                           }
                           if ( populacao.get(i).nota >= populacao.get(o).nota &&  populacao.get(a).nota <= populacao.get(i).nota){
                               pai=populacao.get(i);
                           }
                           if(mae!=pai) break;
                       }
                       o=((int)(Math.random()*mae.ser.size()));
                       individuo filho = new individuo();
                       individuo filha = new individuo();
                       int u=0;
                       while(true){
                            u++;
                           if(u==o) break;

                       }
                       filho.ser.add(pai.ser.get(u));
                       filha.ser.add(mae.ser.get(u));
                       while(true){
                           u++;
                           if(u==mae.ser.size()) break;
                           filho.ser.add(mae.ser.get(u));
                           filha.ser.add(pai.ser.get(u));
                       }

                       while (true){
                           u=filha.verifica();
                           int u1=filho.verifica();
                           if(u==(-1) && u1==(-1)){
                             break;
                           }
                           if(u!=-1 && u1!=(-1)){
                                   int aux;
                                   aux=filha.ser.get(u);
                                   filha.ser.set(u,filho.ser.get(u));
                                   filho.ser.set(u,aux);
                           }
                       }

                       populacao.add(filho);
                       populacao.add(filha);

                   }
                   public void Reinteracao (){
                       Collections.sort(this.populacao);
                       int r = populacao.size();

                       r=r/2;
                       int e=r;
                       r++;

                       while(r<populacao.size()){
                           populacao.remove(r);
                           if (e==populacao.size()){
                               break;
                           }
                       }

                   }



           }

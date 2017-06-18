/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ag;

import java.util.Scanner;

/**
 *
 * @author domiflorzinha
 */
public class Ag {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        System.out.print("O vector esta organizado da seguinte forma: S = 0, E=1, N=2, D=3, M=4, O=5, R=6, Y=7.\n");
        System.out.print("Digite o tamanho da populacao desejada!");
        Scanner ler = new Scanner(System.in);
        int u = ler.nextInt();
        metodos o;
        o = new metodos (); 
        o.Criapop(u);  
        int y=0; //
        while(true){
            if (o.AvaliaPop()){
                System.out.print("Individuo satisfatorio encontrado.\n");
                break;
            }
            else {
               // System.out.print("Dign");
                  o.Cruzamento(); System.out.print("Dign");
                  o.Reinteracao();
            }
            if(y==50) break;
            y++;
        }
        
    }
    
}

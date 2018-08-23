// Problem definition: https://www.spoj.com/problems/CISTFILL/

import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.text.DecimalFormat;

public class Cist {

        static class Tank {
                int b; 
                int h;
                int w; 
                int d;
                int x;          // x equals b+h, position in x axis
                int vol;        // volume as product of 3 dimensions
        }


        public static double vol_sum(Tank[] a, int n, double key_vol) {
                double v = 0.0;

                for (int i = 0; i < n; i++) {
                        if(key_vol > a[i].x)
                                v += a[i].vol;
                        else if(key_vol > a[i].b)
                                v += (key_vol - a[i].b)*a[i].w*a[i].d;
                }
        

                return v;

        }

        public static double binsearch(Tank[] a, int n, int v) {
                double mid, low = 0.0, hi = 1040000.0, result = -1.0;

                while(low < hi) {
                        mid = low + (hi - low) / 2;
                        if(((Math.abs(mid - low)) <= (1e-8)) || ((Math.abs(mid - hi)) <= (1e-8))) break;
                                if(vol_sum(a, n, mid) < v)
                                        low = mid;
                                else {  
                                        result = mid;       
                                        hi = mid;
                                }
                }
        
                return result;
        }


        public static void main (String args[]) {

                File inFile = new File(args[0]);
                try {
                        Scanner scanner = new Scanner(inFile);


                        int max = 0;

                        int n = Integer.parseInt(scanner.nextLine().trim());
                        Tank []a = new Tank[n];

                        for(int i = 0; i < n; i++)  {
                                String s = scanner.nextLine();
                                String[] line = s.split(" ");
                                a[i] = new Tank() ;
                                a[i].b = Integer.parseInt(line[0].trim());
                                a[i].h = Integer.parseInt(line[1].trim());
                                a[i].w = Integer.parseInt(line[2].trim());
                                a[i].d = Integer.parseInt(line[3].trim());
                                a[i].x = a[i].b+a[i].h;
                                a[i].vol = a[i].h*a[i].w*a[i].d;
                                max = Math.max(a[i].x, max);

                        }
        
                        double answer = binsearch(a, n, Integer.parseInt(scanner.nextLine().trim()));
                        scanner.close();


                        if ( (answer == -1) || ((answer - max)>=(1e-7)) )
                                System.out.println("Overflow");
                        else
                                System.out.printf("%.2f\n", answer);
                }
                catch (FileNotFoundException e) {
                        e.printStackTrace();
                }
 
        }   

}

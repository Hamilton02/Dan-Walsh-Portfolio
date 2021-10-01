/* 
 * Author: Daniel Walsh
 * Date: 4/21/21
 * Title: DNS Lookup 
 * Description: Calculate time for HTTP objets to transmit
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(){

  //create input variables
  int conn = 0;
  int object = 0;

  //create RTT variables
  int RTT0 = 3;
  int RTT2 = 20;
  int RTT3 = 26;
  int RTTHTTP = 47;

  //intakes the amount of connections and objects
  printf("How many connections?\n");
  scanf("%d", &conn);
  printf("How many objects?\n");
  scanf("%d", &object);

  //calculate the flow ratio
  double objConn = ceil((double) object/conn);

  //calculate time to do one web request
  int webRequest = RTT0 + RTT2 + RTT3 + (2 * RTTHTTP);

  printf("a: webRequest = %d msecs \n", webRequest);

  //calculate time to do six web requests
  int sixObjects = RTT0 + RTT2 + RTT3 + (2 * RTTHTTP) + (2 * 6 * RTTHTTP);

  printf("b: Request 6 Objects = %d msec \n", sixObjects);

  //calculate time to do persistent and non-persistant with n amount of connections
  int nParallelPerst = RTT0 + RTT2 + RTT3 + (2 * RTTHTTP)  +  (objConn * RTTHTTP);
  int nParallelNonPerst = RTT0 + RTT2 + RTT3 + (2 * RTTHTTP) + (2 * objConn * RTTHTTP);

  printf("c: Persistant = %d msec\n", nParallelPerst);
  printf("c: Non-Persistant = %d msec\n", nParallelNonPerst);

}

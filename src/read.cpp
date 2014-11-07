#include <ros/ros.h>
#include <cereal_port/CerealPort.h>
#include "std_msgs/String.h"
#include <std_msgs/Int16.h>
#include <boost/lexical_cast.hpp>

#define REPLY_SIZE 20
#define TIMEOUT 20
using namespace std;
cereal::CerealPort device;


char reply[15];
char* A;
int h;
int temp1,temp;
std_msgs::Int16 v_co2;
std_msgs::Int16 v_heat;
std::string buf;
ros::Publisher co2_pub;
ros::Publisher temp_pub;
char *pIndex;
char *pCo2;
int Co2;
int IndexCo2;

void teleop_callback(const std_msgs::StringConstPtr& msg)
{
    if(msg->data == "request")
    {

     //   device.readBytes(reply,1000);
      //   ROS_INFO("%s",reply);
      /*  try{
             device.read(reply,10,3000);
             ROS_INFO("%s",reply);

            if(reply[1] == 'z')
            {
                h = ( ((reply[3]-48)*10000)+((reply[4]-48)*1000)+((reply[5]-48)*100)+((reply[6]-48)*10)+(reply[7]-48));

                if(h>100)
                {
                   v_co2.data = h;

                   heat.publish(v_co2);
                   ROS_INFO("CO2 %d", h);
                }
            }
            }
           catch(cereal::Exception& e)
           {
            ROS_ERROR("CO2 Timeout!!!!");
           }*/

    }


}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "co2_sensor");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("teleop_control", 1, teleop_callback);
    //ros::Subscriber sub2 = n.subscribe("speed", 1,"%s",reply SpeedCallback);
 co2_pub= n.advertise<std_msgs::Int16>("co2",10);
temp_pub= n.advertise<std_msgs::Int16>("temperature",10);
    //char reply[REPLY_SIZ50E];

    // Change the next line according to your port name and baud rate

 try
    {
     device.open("/dev/carbon", 9600);
       ros::Duration(0.2).sleep();
    }

    catch(cereal::Exception& e)
    {
        ROS_FATAL("Failed to open the serial port!!!");
        ROS_BREAK();
    }

    ROS_INFO("The serial port is opened.");

    ros::Rate r(0.1);

    //string aa[20];



    while(ros::ok())
    {
        try{
            device.readLine(reply,15,5000);
                       ros::Duration(0.299).sleep();
                       int heat_0 = strtod(reply,&A);
                       int co2  = strtod(A,NULL);
                    v_co2.data = co2;
                    v_heat.data = heat_0;
                       ROS_INFO("%d",heat_0);
                       ROS_INFO("%d",co2);
                       temp_pub.publish(v_heat);
                         co2_pub.publish(v_co2);
      /*  if(reply[1] == 'z')
        {
            h = ( ((reply[3]-48)*10000)+((reply[4]-48)*1000)+((reply[5]-48)*100)+((reply[6]-48)*10)+(reply[7]-48));

            if(h>100)
            {
               v_co2.data = h;              //put h value to ros_parameter v_co2 to publish through co2_pub

               co2_pub.publish(v_co2);
               ROS_INFO("CO2 %d ppm", h);
            }
        }*/
                       memset(reply,0,0);

        }
        catch(cereal::Exception& e)
        {
         ROS_ERROR("CO2 Error!!!!");
          // ros::Duration(0.5).sleep();
        }


           /*if(reply[1] == 'z')
           {
               h = ( ((reply[3]-48)*10000)+((reply[4]-48)*1000)+((reply[5]-48)*100)+((reply[6]-48)*10)+(reply[7]-48));

               if(h>100)
               {
                  v_co2.data = h;

                  heat.publish(v_co2);
                  ROS_INFO("CO2 %d", h);
               }
           }
           r.sleep();

           for(int i=0;i<20;i++)
            reply[i] = 0;*/
    }

    //we will be sending commands of type "twist"
    //geometry_msgs::Twist base_cmd;
   // geometry_msgs::Twist cmdl;

    r.sleep();



            ros::spin();
           // r.sleep();

}

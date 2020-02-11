#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <string>
#include <GpsImu7661/ivsensorgps.h>
#include <GpsImu7661/ivsensorimu.h>
#include <fstream>
using namespace std;
serial::Serial ser;//
// ofstream outgpsimu("gpsimudata.txt");

struct TrajectoryPoint
{
	int id;
	double x;
	double y;
	double z;
	float heading;
};

void write_callback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO_STREAM("Write to serial port"<<msg->data);
	ser.write(msg->data);
}


bool CalculateBlockCS( int u1Count,unsigned char *ucBuffer )
{
	unsigned char CS = 0;
	for (int i=0; i< u1Count; i++) // BUFFER_LENGTH 为为数据字段的长度
	{
		CS ^= ucBuffer[i];
	}

	if (CS==ucBuffer[u1Count+2])
	{
		return 1;
	}
	else
		return 0;

}

void InitializeMsg(GpsImu7661::ivsensorgps &msg)
{
	msg.lon=-1;
	msg.lat=-1;
	msg.height=-1;
	msg.heading=-1000;
	msg.msgflag="non"; //消息类型，如果是“gps”则是三维坐标信息，如果是“imu”则是惯导信息
	msg.velocity=-1;
	msg.acceleration=0;
	msg.isvalid=0;
	msg.status=0;
	msg.pitch=0;
	msg.roll = 0;

  

}

void InitializeimuMsg(GpsImu7661::ivsensorgps &msg)
{
   msg.angx = 0;
   msg.angy = 0;
   msg.yaw = 0;
   msg.accx = 0;
   msg.accy = 0;
   msg.accz = 0;
   msg.msgflag="non";
}

void DecoderINSPVAData(char* gpsdata, int length, GpsImu7661::ivsensorgps &gpsimu_msg){
	int  SectionID;
	char data[4096];
	memcpy(data, gpsdata, length);

	//string data=gpsdata;//
	string strPitch1,strRoll1,strHeight1,strHeading,strLatitude1,strLongitude1,strAzimuth1,strVe,strVn,strVu,strSTA;
	float Ve,Vn,Vu;
//数据格式 $GPFPD, GPSWeek, GPSTime, Heading, Pitch, Track, Latitude, 
//       Longitude, Altitude, Ve , Vn,Vu, Ae , An, Au, Baseline, NSV1, NSV2*cs<CR><LF>
//1 Header FPD 协议头
//2 GPSWeek 自 1980-1-6 至当前的星期数(格林尼治时间) wwww 1451
//3 GPSTime 自本周日 0:00:00 至当前的秒数(格林尼治时间） ssssss.sss 368123.300
//4 3 Heading 偏航角(0~359.99) hhh.hh 102.40
//5 4 Pitch 俯仰角(-90~90) +/-pp.pp 1.01
//6 Roll 横滚角(-180~180) +/-rrr.rr -0.80
//7 6 Lattitude 纬度(-90~90) +/-ll.lllllll 34.1966004
//8 7 Longitude 经度(-180~180) +/-lll.lllllll 108.8551924
//9 8 Altitude 高度,单位(米) +/-aaaaa.aa 80.60
//10 9 Ve 东向速度,单位(米/秒) +/-eee.eee 4. 717
//11 10 Vn 北向速度,单位(米/秒) +/-nnn.nnn 10. 206
//12 11 Vu 天向速度,单位(米/秒) +/-uuu.uuu -0.020
//13 Baseline 基线长度,单位(米) bb.bbb 13.898
//14 NSV1 天线 1 卫星数 nn 11
//15 NSV2 天线 2 卫星数 nn 12
//16 status 低半字节 ASCII 码: 0:初始化
                            //1:粗对准
                            //2:精对准
                            //3:GPS 定位
                            //4:GPS 定向
                            //5:RTK
                            //6:DMI 组合
                            //7:DMI 标定
                            //8:纯惯性
                            //9:零速校正
                            //A:VG 模式
           //高半字节 ASCII 码:
                            //0:GPS
                            //1:BD(定制)
                            //2:双模(定制)
//17 Cs 校验 *hh   *58
//18 <CR> <LF> 固定包尾<CR> <LF>

	if (NULL != strstr(gpsdata, "#INSPVAA")){

		for(int iLoop=0; iLoop<length; iLoop++)
		{
			// 帧头
			if('#' == data[iLoop])
			{
				// SectionID为逗号计数器
				SectionID = 0;
			}
			
			// 帧尾
			if('*' == data[iLoop])
			{	
				continue;
			}
			// 逗号计数
			if(',' == data[iLoop])
			{
				SectionID++;
			}
			else // 数据
			{
				switch(SectionID)
				{ 
				case 19://19
					strHeading += data[iLoop];//航向
					break;
				case 18:
					strPitch1+=data[iLoop];
					break;
				 case 17:
				 	strRoll1+=data[iLoop];
				 	break;
				case 11:
					strLatitude1 += data[iLoop];
					break;
              	case 12:
					strLongitude1 += data[iLoop];
					break;
				case 13:
					strHeight1 +=data[iLoop];
					break;
				case 15:
					strVe += data[iLoop];
					break;
				case 14:
					strVn += data[iLoop];
					break;
				case 16:
					strVu += data[iLoop];
					break;
				case 20:
					strSTA += data[iLoop];
					break;
				default:
					break;
				}
			}			
		}


		InitializeMsg(gpsimu_msg);
		gpsimu_msg.lon=atof(strLongitude1.c_str());
		gpsimu_msg.lat=atof(strLatitude1.c_str());
		gpsimu_msg.height=atof(strHeight1.c_str());
		gpsimu_msg.heading=atof(strHeading.c_str());
		gpsimu_msg.pitch=atof(strPitch1.c_str());
		gpsimu_msg.roll=atof(strRoll1.c_str());

       	Ve=atof(strVe.c_str());
		Vn=atof(strVn.c_str());
		Vu=atof(strVu.c_str());
    		gpsimu_msg.velocity=sqrt(Ve*Ve+Vn*Vn+Vu*Vu);
    // gpsimu_msg.velocity=Vn;
		

		

	}

}

void DecoderIMUData(char* gpsdata, int length, GpsImu7661::ivsensorgps &gpsimu_msg){
	int  SectionID;
	char data[4096];
	memcpy(data, gpsdata, length);
	string str_angx,str_angy,str_angz,str_accx,str_accy,str_accz;
/*
数据格式 :
$GTIMU,GPSWeek,GPSTime,GyroX,GyroY,GyroZ,AccX,AccY,AccZ,Tpr*cs<CR><LF>
最高输出速率：100HZ
1. 协议头 "$GTIMU"
2. GPSWeek 自 1980-1-6 至当前的星期数(格林尼治时间) wwww 1451
3. GPSTime 自本周日 0:00:00 至当前的秒数(格林尼治时间） ssssss.sss 368123.300
4. GyroX 陀螺仪 X 轴角速率,单位(度/秒) ±ggg.gggg 0.0140
5. GyroY 陀螺仪 Y 轴角速率,单位(度/秒) ±ggg.gggg 0.0012
6. GyroZ 陀螺仪 Z 轴角速率,单位(度/秒) ±ggg.gggg 0.0032
7. AccX 加速度计 X 轴加速度,单位为(g) ±aaa.aaaa 0.0001
8. AccY 加速度计 Y 轴加速度,单位为(g) ±aaa.aaaa 0.0001
9. AccZ 加速度计 Z 轴加速度,单位为(g) ±aaa.aaaa 1.0001
10. Tpr 温度,单位为摄氏度 ±tt.t -35.7
11. Cs 校验 *hh *56
12. <CR><LF> 固定包尾    <CR><LF>
*/
	if (NULL!=strstr(gpsdata, "#CORRIMUDATAA"))
	{
	for(int iLoop=0; iLoop<length; iLoop++)
	{
		// 帧头
		if('#' == data[iLoop])
		{
			// SectionID为逗号计数器
			SectionID = 0;
		}

		// 帧尾
		if('*' == data[iLoop])
		{	
			continue;
		}
		// 逗号计数
		if(',' == data[iLoop])
		{
			SectionID++;
		}
		else // 数据
		{
			switch(SectionID)
			{ 
			case 11://PitchRate
			    str_angx += data[iLoop];
				break;
			case 12://YawRate
			    str_angy += data[iLoop];
				break;
			case 13: //RollRate
				str_angz += data[iLoop];
				break;
			case 14://LateralAcc
			    str_accx += data[iLoop];
				break;
			case 15://LongitudinalAcc
			    str_accy += data[iLoop];
				break;
			case 16://VeticalAcc
			    str_accz += data[iLoop];
				break;      
			default:
				break;
			}
		}			
	}


		InitializeimuMsg(gpsimu_msg);
		gpsimu_msg.angx=atof(str_angx.c_str());
		gpsimu_msg.angy=atof(str_angy.c_str());
		gpsimu_msg.yaw=atof(str_angz.c_str());
		gpsimu_msg.accx=atof(str_accx.c_str());
		gpsimu_msg.accy=atof(str_accy.c_str());
		gpsimu_msg.accz=atof(str_accz.c_str());
		
	}

}


int id=0;

int main(int argc, char** argv){


	  //创建时间命名记录文件
	time_t currtime = time(NULL);  
    tm* p = localtime(&currtime);  
    char filename[100] = {0};  
    sprintf(filename,"/home/lbc/lbcgps/trace%d%02d%02d%02d%02d%02d.txt",p->tm_year+1900,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);  
    ofstream outgpsimu(filename);
	//创建记录文件结束
	
	int ReceiveGPSLength=0;
	char ReceiveGPSData[4096];
	memset(ReceiveGPSData, 0, 4096);

	char temp_receive[4096];


	int iposGPS=0;// weizhi
	int iposIMU=0;
	char szGPS[4096];  //shuju
	int szGPSLengh=0;  //changdu

	int ReceiveIMULength=0;
	char ReceiveIMUData[4096];
	memset(ReceiveIMUData, 0, 4096);

	char szIMU[4096];
	int szIMULength=0;

	char *pBegin=NULL;
	char *pEnd=NULL;

	char *pBegin2=NULL;
	char *pEnd2=NULL;
	GpsImu7661::ivsensorgps gps_msg;//gps坐标数据
	//GpsImu7662::ivsensorimu imu_msg;//imu运动状态数据
	TrajectoryPoint recordP;
	


	ros::init(argc,argv,"serial_example_node");
	ros::NodeHandle nh;
	ros::Subscriber write_sub = nh.subscribe("write",1000, write_callback);
	//ros::Publisher imu_pub = nh.advertise<GpsImu7662::ivsensorimu>("/gpsimu",1000);
	ros::Publisher gps_pub = nh.advertise<GpsImu7661::ivsensorgps>("/gpsimu",1000);
	try{
		ser.setPort("/dev/ttyS0");
		ser.setBaudrate(115200);
		serial::Timeout to = serial::Timeout::simpleTimeout(1000);
		ser.setTimeout(to);
		ser.open();
	}
	catch(serial::IOException &e){
		ROS_ERROR_STREAM("Unable to open port");//
		return -1;
	}

	if(ser.isOpen()){
		ROS_INFO_STREAM("Serial Port initialized");
	}
	else{
		return -1;
	}

	ros::Rate loop_rate(20);//10HZ
	while(ros::ok()){

		if(ser.available()){
			ROS_INFO_STREAM("Reading from serial port\n");
			

			std_msgs::String result;
			result.data = ser.read(ser.available());
			if(ReceiveGPSLength+result.data.length()>1000)
			{
				ReceiveGPSLength=0;
			}
			for (int i = 0; i < result.data.length(); ++i)
			{
				ReceiveGPSData[ReceiveGPSLength+i]=result.data[i];
			}
			ReceiveGPSLength=ReceiveGPSLength+result.data.length();


			if(ReceiveIMULength+result.data.length()>1000)
			{
				ReceiveIMULength=0;
			}
			for (int i = 0; i < result.data.length(); ++i)
			{
				ReceiveIMUData[ReceiveIMULength+i]=result.data[i];
			}
			ReceiveIMULength=ReceiveIMULength+result.data.length();


			pBegin = strstr(ReceiveGPSData, "#INSPVAA");

			if (pBegin!=NULL)//GPS解析
			{	

				ROS_INFO_STREAM("FIND gps");	
				
				//再找BESTXYZA
				iposGPS=pBegin-ReceiveGPSData;   	
				pEnd = strchr(pBegin, '*');	

				if(pEnd != NULL)
				{				
					// 长度(包括帧尾)
					szGPSLengh = pEnd - pBegin+9;

					if((ReceiveGPSLength-iposGPS)>=szGPSLengh)
					{			
						// 初始化GPGGA语句缓存数据
						memset(szGPS, 0, 4096);

						// 转存数据
						memcpy(szGPS, pBegin, szGPSLengh);
						
                         
						// 校验成功后解析BEST语句数据		
						//if(CalculateBlockCS(szGPSLengh-10,(unsigned char*)(szGPS+1)))
						{
							DecoderINSPVAData(szGPS, szGPSLengh, gps_msg);
							gps_msg.msgflag="gps_msg";
							gps_msg.header.stamp = ros::Time::now();
							//gps_msg.header.frame_id = "imu_link";
							//gps_pub.publish(gps_msg);//发送坐标
							//ROS_INFO_STREAM("find gpfpd");
							ROS_INFO_STREAM("gps");
							ROS_INFO_STREAM(gps_msg);

						}
							

						// 清空GPS数据缓存
						ReceiveGPSLength = ReceiveGPSLength-szGPSLengh-iposGPS;
						//ReceiveData=pEnd+5;
						memcpy(temp_receive,pEnd+9, ReceiveGPSLength);
						memset(ReceiveGPSData, 0, 4096);
						memcpy(ReceiveGPSData,temp_receive, ReceiveGPSLength);
					}
				}
				
			}

			
			pBegin2 = strstr(ReceiveIMUData, "#CORRIMUDATAA");
			if (pBegin2!=NULL)//imu解析
			{		
				ROS_INFO_STREAM("FIND imu");
				//再找BESTXYZA
				iposIMU = pBegin2-ReceiveIMUData;   	
				pEnd2 = strchr(pBegin2, '*');	

				if(pEnd2 != NULL)
				{				
					// 长度(包括帧尾)
					szIMULength = pEnd2 - pBegin2+9;

					if((ReceiveIMULength-iposIMU)>=szIMULength)
					{			
						// 初始化GPGGA语句缓存数据
						memset(szIMU, 0, 4096);

						// 转存数据
						memcpy(szIMU, pBegin2, szIMULength);
                         
						// 校验成功后解析BEST语句数据		
						//if(CalculateBlockCS(szGPSLengh-10,(unsigned char*)(szGPS+1)))
						{
							DecoderIMUData(szIMU, szIMULength, gps_msg);
							//imu_msg.msgflag="imu_msg";
							// gpsimu_pub.publish(imu_msg);//发送坐标
							//imu_pub.publish(imu_msg);
							ROS_INFO_STREAM("imu");
							//ROS_INFO_STREAM(imu_msg);
						}
							

						// 清空GPS数据缓存
						ReceiveIMULength = ReceiveIMULength-szIMULength-iposIMU;
						memcpy(temp_receive,pEnd2+9, ReceiveIMULength);
						memset(ReceiveIMUData, 0, 4096);
						memcpy(ReceiveIMUData,temp_receive, ReceiveIMULength);
					}
				}
				
			}

			recordP.x=gps_msg.lat;
			recordP.y=gps_msg.lon;
			recordP.z=gps_msg.velocity;
			recordP.heading=gps_msg.heading;
			recordP.id=id;
			if(recordP.x!=0 && recordP.y!=0)
		     	outgpsimu<<setprecision(12)<<recordP.id<<"\t"<<recordP.x<<"\t"<<recordP.y<<"\t"<<recordP.z<<"\t"<<recordP.heading<<endl;
			id++;

			gps_pub.publish(gps_msg);
			
		}
		ros::spinOnce();
		loop_rate.sleep();
	}
}

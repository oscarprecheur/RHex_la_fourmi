/*
 * main.c
 *
 *  Created on: 27 mai 2016
 *      Author: laurent
 */

#include "main.h"
#include "bsp.h"
#include "delay.h"
#include "can_fct.h"
#include "encoder_fct.h"
#include "math.h"
#include "Sampler.h"
#include "PWM.h"
#include "speed.h"


float q0 = 0;
float q1 = 0;
float q2 = 0;
float q3 = 0;

float qanc=0;

float qs ;

int arrive[4] ={0, 0, 0, 0} ;
int var = 0;


uint8_t pb_state;

uint8_t sample_interrupt = 0;
uint8_t PB_interrupt = 0;
uint8_t com_pc = 0;
uint8_t printed = 1;

int set_motor(uint8_t motor, __IO uint32_t * CCRX, float q, float consigne);
uint16_t get_duty(float dq, float q);

/* consigne must be in [-180; 180] */
float consigne[4] = {30 , 0, 0, 0}; // Moteur : 1, 2, 3, 4
float marche[4][126] = {{11.3099324740202,11.2961616575843,11.2548757110376,11.1861542391944,11.0901302354925,10.9669905495625,10.8169765208001,10.6403847571189,10.4375680324071,10.2089362708167,9.95495758095409,9.67615929841833,9.37312899106077,9.04651537794541,8.69702911040110,8.32544336192364,7.93259417313868,7.51938049871001,7.08676390508202,6.63576787136726,6.16747665057937,5.68303365477154,5.18363933542379,4.67054853951724,4.14506733197158,3.60854928626625,3.06239125682513,2.50802865877388,1.94693029259666,1.38059276262036,0.810534548729276,0.238289799870917,-0.334598074602080,-0.906582934195952,-1.47612247226904,-2.04168473089048,-2.60175448108521,-3.15483938768582,-3.69947588387429,-4.23423468828467,-4.75772590694329,-5.26860367298187,-5.76557028857565,-6.24737984552302,-6.71284131289321,-7.16082109184665,-7.59024504874439,-8.00010004772242,-8.38943501279249,-8.75736155707962,-9.10305422292201,-9.42575038119935,-9.72474984143496,-9.99941422599101,-10.2491661621354,-10.4734883450209,-10.6719225228111,-10.8440684524590,-10.9895828711200,-11.1081785240138,-11.1996232848412,-11.2637393997432,-11.3004028803413,-11.3095430657152,-11.2911423673182,-11.2452362048619,-11.1719131351777,-11.0713151700170,-10.9436382727424,-10.7891330179253,-10.6081053920596,-10.4009177079910,-10.1679896003117,-9.90979906397937,-9.62688349387893,-9.31984067908178,-8.98932970228324,-8.63607169246643,-8.26085037737789,-7.86451238205084,-7.44796722050169,-7.01218692996310,-6.55820530068324,-6.08711665945881,-5.60007417167316,-5.09828763462441,-4.58302074422876,-4.05558782759309,-3.51735004522035,-2.96971107844131,-2.41411232970450,-1.85202767521548,-1.28495782069040,-0.714424321269460,-0.141963335534938,0.430880809249012,1.00256215840056,1.57153969238026,2.13628382485067,2.69528275221931,3.24704857472567,3.79012311533759,4.32308337080595,4.84454653886927,5.35317457643106,5.84767825515393,6.32682069291366,6.78942035153631,7.23435350283009,7.66055617579249,8.06702560775074,8.45282123086283,8.81706523271985,9.15894273565909,9.47770164378949,9.77265220966947,10.0431663741226,10.2886769329257,10.5086765831779,10.7027169001864,10.8704072928336,11.0114139817501,11.1254590403491,11.2123195339937,11.2718267873899,11.3038658048020},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{-9.09697309965812,-8.60291878626176,-8.11149251801888,-7.62388362866257,-7.14126388998253,-6.66478523435716,-6.19557753742088,-5.73474645901263,-5.28337134231717,-4.84250317286785,-4.41316260075364,-3.99633803088243,-3.59298378742220,-3.20401835950514,-2.83032273587096,-2.47273883630447,-2.13206804745187,-1.80906986987412,-1.50446068202329,-1.21891262524832,-0.953052612010953,-0.707461457308611,-0.482673130966942,-0.279174126107048,-0.0974029368455294,0.0622503637090838,0.199444455713786,0.313887026767474,0.405334960198032,0.473594469534235,0.518521190456998,0.540020240107881,0.538046251648213,0.512603389516153,0.463745348060626,0.391575333304519,0.296246024676234,0.177959510825035,0.0369671912570488,-0.126430366366244,-0.311883624738193,-0.518994343366376,-0.747315925128159,-0.996353854439323,-1.26556623734630,-1.55436445216683,-1.86211391725635,-2.18813498020316,-2.53170393039169,-2.89205413455612,-3.26837729279922,-3.65982481067806,-4.06550928144379,-4.48450607142331,-4.91585500088052,-5.35856211250235,-5.81160151990370,-6.27391732920470,-6.74442562775221,-7.22201653537219,-7.70555631508304,-8.19388954189215,-8.68584133006303,-9.18021962099900,-9.67581753556376,-10.1714157961773,-10.6657852253179,-11.1576893280637,-11.6458869669634,-12.1291351377840,-12.6061918545037,-13.0758191512608,-13.5367862078127,-13.9878726033929,-14.4278717016652,-14.8555941667866,-15.2698716074250,-15.6695603419793,-16.0535452742824,-16.4207438648096,-16.7701101779730,-17.1006389815634,-17.4113698699531,-17.7013913784319,-17.9698450521800,-18.2159294300357,-18.4389039005638,-18.6380923861024,-18.8128868096026,-18.9627502992768,-19.0872200873967,-19.1859100620763,-19.2585129345135,-19.3048019888815,-19.3246323877696,-19.3179420125974,-19.2847518255991,-19.2251657475659,-19.1393700533132,-19.0276322945507,-18.8902997672440,-18.7277975474285,-18.5406261255688,-18.3293586747819,-18.0946379924272,-17.8371731576312,-17.5577359492185,-17.2571570692728,-16.9363222172054,-16.5961680578435,-16.2376781247903,-15.8618786972857,-15.4698346851711,-15.0626455524803,-14.6414413058169,-14.2073785691777,-13.7616367623816,-13.3054143959062,-12.8399254908062,-12.3663961286025,-11.8860611326400,-11.4001608794865,-10.9099382365045,-10.4166356198035,-9.92149216537138,-9.42574100528074},
{-97.1646202550987,-97.7112815464281,-98.2567002934371,-98.7995602302041,-99.3385482508393,-99.8723567538081,-100.399686065077,-100.919246950581,-101.429763226031,-101.929974469351,-102.418638838108,-102.894535991141,-103.356470110424,-103.803273015855,-104.233807362406,-104.646969905806,-105.041694819833,-105.416957045377,-105.771775648757,-106.105217164452,-106.416398895449,-106.704492142887,-106.968725335627,-107.208387029880,-107.422828749012,-107.611467634218,-107.773788877881,-107.909347913049,-108.017772334631,-108.098763530510,-108.152098003800,-108.177628370862,-108.175284023355,-108.145071446522,-108.087074189923,-108.001452490978,-107.888442555763,-107.748355505551,-107.581576001456,-107.388560563135,-107.169835600889,-106.925995183399,-106.657698565922,-106.365667505805,-106.050683393735,-105.713584230165,-105.355261476835,-104.976656813206,-104.578758827045,-104.162599667242,-103.729251685373,-103.279824090474,-102.815459639117,-102.337331380145,-101.846639470496,-101.344608075387,-100.832482362886,-100.311525599610,-99.7830163509863,-99.2482457863192,-98.7085150857937,-98.1651329436620,-97.6194131591477,-97.0726723041859,-96.5262274549870,-95.9813939726208,-95.4394833163941,-94.9018008727698,-94.3696437819782,-93.8442987443235,-93.3270397885215,-92.8191259852278,-92.3217990902542,-91.8362811038245,-91.3637717345954,-90.9054457600438,-90.4624502781881,-90.0359018494124,-89.6268835313522,-89.2364418143028,-88.8655834693254,-88.5152723260446,-88.1864260019153,-87.8799126093479,-87.5965474713526,-87.3370898801381,-87.1022399362115,-86.8926355078233,-86.7088493519486,-86.5513864382770,-86.4206815168318,-86.3170969678072,-86.2409209690178,-86.1923660120497,-86.1715677928975,-86.1785844967119,-86.2133964894705,-86.2759064221308,-86.3659397453845,-86.4832456257567,-86.6274982467320,-86.7982984720798,-86.9951758428020,-87.2175908743093,-87.4649376166766,-87.7365464382170,-88.0316869911778,-88.3495713180906,-88.6893570581361,-89.0501507147288,-89.4310109482513,-89.8309518613340,-90.2489462481225,-90.6839287834389,-91.1347991324573,-91.6004249663374,-92.0796448740392,-92.5712711651609,-93.0740925630002,-93.5868767910388,-94.1083730596398,-94.6373144628688,-95.1724202979744,-95.7123983221788,-96.2559469630186,-96.8017574995556}};


int set_motor(uint8_t motor, __IO uint32_t * CCRX, float q, float consigne)
{
    float dq;
    float q_main = q;
    uint16_t duty;


    if(fabs(q) > 180)
    {
        if(q < 0)
            q_main = q + 360;
        else if(q > 0)
            q_main = q - 360;
    }

    dq = consigne - q_main;

    if(motor == 1 || motor == 2)
        dq = -dq;

    duty = get_duty(dq, q_main);

    *CCRX = duty;
    int dq_int = 0 ;
    int dq_dec = 0;

    if (dq < 0 )
    {
    	dq_int=floor(dq)+1;
    	dq_dec=(int)((dq_int-dq)*1000);
    }
    else
    {
    	dq_int = floor(dq) ;
    	dq_dec=(int)((dq-dq_int)*1000);
    }
    my_printf("dq = %d,%d\n",dq_int,dq_dec);
    if( (dq > -close_angle) && (dq < close_angle) )
    	{
    		return 1;
    	}
    else
    	return 0;
}

uint16_t get_duty(float dq, float q)
{
	// Donne l'angle correspondant à l'erreur courante
/*
    if(dq > -close_angle && dq < close_angle)
    {
        uint16_t index_duty;
        index_duty = size_duty_table*(dq+close_angle)/(2*close_angle);
        return duty[index_duty];
    }
    if(dq < -close_angle)
        return duty_min;
    else
        return duty_max;
*/

	float duty;
	float Kp = 30;
	float Kd = 20;

	if(dq > -close_angle && dq < close_angle)
	{
		duty = period_PWM/2;
	}
	else if(dq <= -close_angle)
	{
		duty = -fmin((Kp*dq + Kd*(dq-qanc)),-800) + period_PWM/2;
	}
	else
	{
		duty = -fmax((Kp*dq + Kd*(dq-qanc)),800) + period_PWM/2;
	}
	qanc = dq ;
	return duty;


}


	  /* Decommenter la partie correspondante*/

/*§----------§ Configuration des codeurs §----------§*/
/*int main()
{
	// Toutes les opperations se font sur le CAN1
	// Le cable du codeur doit etre connecte au port "CAN1" !!!


	SystemClock_Config();  //Switch to HSE, 168MHz
	SysTick_Init(); 	   //Init fct delay_ms
	BSP_LED_Init();		   //Init GPIO for LEDS
	BSP_PB_Init();         //Init push button (PC13) for interrupt
	BSP_USART_PC_Init();   //Init console

	my_printf("\n\r");

	// Init du CAN n°1
	CAN1_GPIO_Config();
	RCC->APB1ENR |= CAN1_CLK; // Enable CAN1 clock
	CAN_DeInit(CAN1);
	CAN_BaudRate_Init(CAN1, BaudRate_250kb); // La vitesse de communication par defaut d'un codeur
	CAN_Filter_Config(CAN1);


//	my_printf("\n\rDebut\n");
//	write_msg(CAN1, 0x000, 2, 0x013E , 1); // Set op mode
//	read_msg(CAN1, 1);


	my_printf("\n\n\n\n\rShall We Begin ?\n\rPress The Blue Button To Start:");

	while ( !PB_interrupt ); // On lance le programme
	PB_interrupt = 0;

	my_printf("\n\rStarted: \n");
	uint16_t dt_ms = 10000; // on donne (environ !, a tester !) 10 secondes pour choisir le mode
	TIM3_Init(dt_ms);


	while (sample_interrupt == 0) // on choisi ce que l'on veut faire avec le bouton bleu
	{
		if (PB_interrupt)
			{
				PB_interrupt = 0;
				i++;
			}

		if (i == 0)
		{
			BSP_LED_On(0);
			BSP_LED_Off(1);
			BSP_LED_Off(2);
			my_printf("\rNothing         ");
		}

		if (i ==1)
		{
			BSP_LED_Off(0);
			BSP_LED_On(1);
			BSP_LED_Off(2);
			my_printf("\rProgram Node 3F ");
		}
		if (i == 2)
		{
			BSP_LED_Off(0);
			BSP_LED_Off(1);
			BSP_LED_On(2);
			my_printf("\rProgram Node 3E ");
		}

		if (i > 2)
			i = 0;
	}

	if (i == 0)
	{
		my_printf("\rSTART Nothing         \n");
		my_printf("\rNothing...      \n");
		my_printf("\rEND Nothing         \n");
	}

	if(i == 1)
	{
		my_printf("\r\nSTART 3F address:\n\n\r");

		//my_printf("\r****** Set to 250kHz baude rate\n");
		//write_msg(CAN1, 0x63F, 8, 0x2F00210005000000 , 1); // Set to 250kHz baude rate
		//read_msg(CAN1, 1);
		//my_printf("\n");

		my_printf("\r****** Set node address to 3f\n");
		write_msg(CAN1, 0x63F, 8, 0x2F0121003F000000 , 1); // Set node address to 3f
		read_msg(CAN1, 1);
		my_printf("\n");

		my_printf("\r****** Set termination resistor off\n");
		write_msg(CAN1, 0x63F, 8, 0x2F02210000000000 , 1); // Set termination resistor off / "Termination off"
		read_msg(CAN1, 1);
		my_printf("\n");

		my_printf("\r****** Set to 1000kHz baude rate\n");
		write_msg(CAN1, 0x63F, 8, 0x2F00210008000000 , 1); // Set to 1000kHz baude rate
		read_msg(CAN1, 1);
		my_printf("\n");

		my_printf("\r****** Save all bus objects\n");
		write_msg(CAN1, 0x63F, 8, 0x2305210073617665 , 1); // Save all bus objects
		read_msg(CAN1, 1);

		my_printf("\n\rPlease now, shut down the encoder\n");


	}

	if(i == 2)
	{
		my_printf("\n\rSTART 3E address:\n\n");

		//my_printf("\r****** Set to 250kHz baude rate\n");
	    //write_msg(CAN1, 0x63E, 8, 0x2F00210005000000 , 1); // Set to 250kHz baude rate
		//read_msg(CAN1, 1);
		//my_printf("\n");

		my_printf("\r****** Set node address to 3e\n");
		write_msg(CAN1, 0x63F, 8, 0x2F0121003E000000 , 1); // Set node address to 3f
		read_msg(CAN1, 1);
		my_printf("\n");

		my_printf("\r****** Set termination resistor off\n");
		write_msg(CAN1, 0x63F, 8, 0x2F02210000000000 , 1); // Set termination resistor off / "Termination off"
		read_msg(CAN1, 1);
		my_printf("\n");

		my_printf("\r****** Set to 1000kHz baude rate\n");
		write_msg(CAN1, 0x63F, 8, 0x2F00210008000000 , 1); // Set to 1000kHz baude rate
		read_msg(CAN1, 1);
		my_printf("\n");

		my_printf("\r****** Save all bus objects\n");
		write_msg(CAN1, 0x63F, 8, 0x2305210073617665 , 1); // Save all bus objects
		read_msg(CAN1, 1);

		my_printf("\n\rPlease now, shut down the encoder\n");

	}

		my_printf("\n\rEnd");
}*/
/*§------------------------------------------------§*/


/*§-------§ Mise en mouvement d'une patte §-------§*/
int main()
{
    // Switch to HSE, 168MHz
    SystemClock_Config();

    // Init fct delay_ms
    SysTick_Init();

    // Init GPIO for LEDS
    BSP_LED_Init();

    // Init push button (PC13) for interrupt
    BSP_PB_Init();

    // Init console
	BSP_USART_PC_Init();   //Init console

	my_printf("\n\rDebut\n");
    // Create an interruption every dt_ms
    uint16_t dt_ms = 10;
    TIM3_Init(dt_ms);

    // Init ADC
    BSP_ADC_Init();

    BSP_LED_On(0); // Led 0 to test

    Motor1234_PWM_Init();

	my_printf("\n PMW ENVOYEE \n ");
	TIM1->CCR1 = period_PWM/2; // PE9    : q0 -> CAN2_3F
    TIM1->CCR2 = period_PWM/2; // PE11   : q1 -> CAN2_3E
	TIM1->CCR3 = period_PWM/2; // PE13   : q2 -> CAN1_3E
	TIM1->CCR4 = period_PWM/2; // PE14   : q3 -> CAN1_3F

	  CAN_Config(BaudRate_1000kb, BaudRate_1000kb); // CAN1 and CAN2 set to 1000kb
	  my_printf("\n can config ok \n ");

	  	  mode_Pre_Operationnel(CAN1, 0x3F); // Encoder 3F on CAN1 enter in pre-operational mode
	      mode_Pre_Operationnel(CAN1, 0x3E); // Idem for 3E, CAN1
	      mode_Pre_Operationnel(CAN2, 0x3F); // Idem for 3F, CAN2
	      mode_Pre_Operationnel(CAN2, 0x3E); // Idem for 3E, CAN2
	      my_printf("\n mode pre op ok\n ");


	      my_printf("\n P4 positions ok \n ");

	      mode_Operationnel(CAN2, 0x3F); // Encoder 3F on CAN2 enter in operational mode
	      mode_Operationnel(CAN2, 0x3E); // Idem for 3E, CAN2
	      mode_Operationnel(CAN1, 0x3F); // Idem for 3F, CAN1
	      mode_Operationnel(CAN1, 0x3E); // Idem for 3E, CAN1

	      my_printf("\n mode ope ok  \n ");

	      int s;
	      s = 126;

    while(1)
    {
    // PWM Period definition : half = no movement
    //TIM1->CCR1 = period_PWM/2; // PE9    : q0 -> CAN2_3F
    //TIM1->CCR2 = period_PWM/2; // PE11   : q1 -> CAN2_3E
    //TIM1->CCR3 = period_PWM/2; // PE13   : q2 -> CAN1_3E
    //TIM1->CCR4 = period_PWM/2; // PE14   : q3 -> CAN1_3F

    	if (PB_interrupt)
    		      	{
    		    	  	  reset_4Positions(); //If

    		    	  	 mode_Operationnel(CAN2, 0x3F); // Encoder 3F on CAN2 enter in operational mode
    		    	     mode_Operationnel(CAN2, 0x3E); // Idem for 3E, CAN2
    		    	  	 mode_Operationnel(CAN1, 0x3F); // Idem for 3F, CAN1
    		    	  	 mode_Operationnel(CAN1, 0x3E); // Idem for 3E, CAN1

    		      	}
    	PB_interrupt = 0;


    	//consigne[0] = marche[0][var];
    	//consigne[1] = marche[1][var];
    	//consigne[2] = marche[2][var];
    	//consigne[3] = marche[3][var];

				// qX is the current angle
				get_2Angles(CAN1, TPDO1, &q3, &q2); // get angle 3F & 3E from CAN1
				get_2Angles(CAN2, TPDO1, &q0, &q1); // get angle 3F & 3E from CAN2
				int q0_int=floor(q0);
				int q0_dec=(int)((q0-q0_int)*1000);
				int q1_int=floor(q1);
				int q1_dec=(int)((q1-q1_int)*1000);
				int q3_int=floor(q3);
				int q3_dec=(int)((q3-q3_int)*1000);
				int q2_int=floor(q2);
				int q2_dec=(int)((q2-q2_int)*1000);
				qs = q0;
				my_printf("\n\r c1 q0 : ");
				my_printf("%d,%d",q0_int,q0_dec);
				my_printf("\n\r c1 q1 : ");
				my_printf("%d,%d",q1_int,q1_dec);
				my_printf("\n\r c2 q2 : ");
				my_printf("%d,%d",q2_int,q2_dec);
				my_printf("\n\r c2 q3 :");
				my_printf("%d,%d",q3_int,q3_dec);
				my_printf("\n\rfin fin\n");
				//for( int i =0 ; i<100000; i++);
				// Motor running to "consigne[X]" angle
				arrive[0] = set_motor(1, &(TIM1->CCR1), q0, consigne[0]);
				arrive[1] = set_motor(2, &(TIM1->CCR2), q1, consigne[1]);
				arrive[2] = set_motor(3, &(TIM1->CCR3), q2, consigne[2]);
				arrive[3] = set_motor(4, &(TIM1->CCR4), q3, consigne[3]);
				my_printf("Arrive %d, %d, %d, %d",arrive[0], arrive[1],arrive[2],arrive[3]);
				if (arrive[0] == 1 && arrive[1] == 1 && arrive[2] == 1 && arrive[3] == 1 )
				{

					var = var+8;
					if (var >= s) var = 0;
					my_printf("var = %d", var);
				}

    }
}
/*§-----------------------------------------------§*/




/* Interruption created every dt_ms */
void TIM3_IRQHandler()
{
    if((TIM3->SR & 0x0001) && (TIM3->DIER & 0x0001))
    {
        sample_interrupt = 1;

        TIM3->SR = ~(0x0001);
    }
}

/* Interruption created by push button */
void EXTI15_10_IRQHandler()
{
    if(EXTI->PR & 0x02000)
    {
        PB_interrupt = 1;
        EXTI->PR = 0x02000;
    }
}

/* RX Terminal Interrupt, DO NOT WORK YET*/
void DMA1_Stream1_IRQHandler(void)
{

	// Test if this is a HT interrupt
	if ( (DMA1->LISR & DMA_LISR_HTIF1) == DMA_LISR_HTIF1 )
	{
		// Clear HT flag
		DMA1->LIFCR |= DMA_LIFCR_CHTIF1;
		//com_pc = 1;
	}

	// Test if this is a TC interrupt
	if ( (DMA1->LISR & DMA_LISR_TCIF1) == DMA_LISR_TCIF1 )
	{
		// Clear TC flag
		DMA1->LIFCR |= DMA_LIFCR_CTCIF1;

		com_pc = 1;
	}
}

/* General Clock Config */
static void SystemClock_Config()
{
    uint32_t    HSE_Status;
    uint32_t    timeout = 0;

    // Start HSE

    RCC->CR |= RCC_CR_HSEBYP;
    RCC->CR |= RCC_CR_HSEON;

    // Wait until HSE is ready
    do
    {
        HSE_Status = RCC->CR & RCC_CR_HSERDY;
        timeout++;
    } while ((HSE_Status == 0) && (timeout != 0x0500));

    // Enable the power regulator scale mode 1

    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= 0x03 <<14;

    // Configure the main PLL

    #define PLL_M   8       // 8MHz HSE down-to 1MHz PLL input
    #define PLL_N   336     // 336 MHz VCO output
    #define PLL_P   2       // 168 MHz PLL output
    #define PLL_Q   7       // 48  MHz (USB)

    RCC->PLLCFGR = PLL_M | (PLL_N <<6) | (((PLL_P >> 1) -1) << 16) | (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

    // Enable the main PLL

    RCC-> CR |= RCC_CR_PLLON;

    // Enter Over-drive power mode

    PWR->CR |= PWR_CR_ODEN;
    while ((PWR->CSR & PWR_CSR_ODRDY) == 0);

    PWR->CR |= PWR_CR_ODSWEN;
    while ((PWR->CSR & PWR_CSR_ODSWRDY)==0);

    // Configure Prefetch and wait state (increase wait states at 216 MHz)

    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_4WS;

    // Configure AHB/APB prescalers
    // AHB  Prescaler = /1  -> 168 MHz
    // APB1 Prescaler = /4  -> 42  MHz
    // APB2 Prescaler = /2  -> 84 MHz

    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

    // Wait until PLL is ready

    while((RCC->CR & RCC_CR_PLLRDY) == 0);

    // Select the main PLL as system clock source

    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    // Wait until PLL is switched on

    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

    // Update System core clock

    SystemCoreClockUpdate();
}

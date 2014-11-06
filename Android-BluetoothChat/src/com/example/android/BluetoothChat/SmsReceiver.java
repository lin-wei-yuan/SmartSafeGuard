/**
 * 
 */
package com.example.android.BluetoothChat;

//import org.crazyit.ui.ToastTest;

//import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
//import android.graphics.Color;
import android.os.Bundle;
import android.telephony.SmsMessage;
import android.view.Gravity;
//import android.view.LayoutInflater;
//import android.view.View;
//import android.view.ViewGroup;
//import android.widget.ImageView;
//import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;



/**
 * Description:
 * <br/>��վ: <a href="http://www.crazyit.org">���Java����</a> 
 * <br/>Copyright (C), 2001-2012, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class SmsReceiver extends BroadcastReceiver
{	
	
	// �����յ�����ʱ������
	@Override
	public void onReceive(Context context, Intent intent)
	{
		
		// ����ǽ��յ�����
		if (intent.getAction().equals(
			"android.provider.Telephony.SMS_RECEIVED"))
		{
			
			
			
			// ȡ���㲥�����д��뽫����ϵͳ�ղ������ţ�
			//abortBroadcast();
			//��ϵͳҲ���ն��� 	���ڱ���
			
			
			
			
			
			StringBuilder sb = new StringBuilder();
			// ������SMS������������
			Bundle bundle = intent.getExtras();
			// �ж��Ƿ�������
			if (bundle != null)
			{
				//  ͨ��pdus���Ի�ý��յ������ж�����Ϣ
				Object[] pdus = (Object[]) bundle.get("pdus");
				// �������Ŷ���array,�������յ��Ķ��󳤶�������array�Ĵ�С 
				SmsMessage[] messages = new SmsMessage[pdus.length];
				
				
				for (int i = 0; i < pdus.length; i++)
				{
					messages[i] = SmsMessage
						.createFromPdu((byte[]) pdus[i]);
				}
				
				// �������Ķ��źϲ��Զ�����Ϣ��StringBuilder���� 
				/*
				for (SmsMessage message : messages)
				{
					//sb.append("������Դ:");
					// ��ý��ն��ŵĵ绰����
					//sb.append(message.getDisplayOriginatingAddress());
					sb.append("���ܰ�ȫ��ʿ��ʾ\n");
					
					//sb.append("\n------��������------\n");
					// ��ö��ŵ�����
					sb.append(message.getDisplayMessageBody());
				}
				*/
				//���ڶ��ŵ�Toast����Ч������ ��ȥ
			}
			
			//Toast toast = Toast.makeText(context,sb.toString(), 5000);
			
			
			
			//����������� ʧ��
			/*
				LayoutInflater inflater = (LayoutInflater) ((Activity) context).getLayoutInflater();
			   View layout = inflater.inflate(R.layout.picture,
			     (ViewGroup) ((Activity) context).findViewById(R.id.picture));
			   ImageView image = (ImageView) layout
			     .findViewById(R.id.cold_play);
			   image.setImageResource(R.drawable.cold_play);
			   TextView title = (TextView) layout.findViewById(R.id.tvTitleToast);
			   title.setText("Attention");
			   TextView text = (TextView) layout.findViewById(R.id.tvTextToast);
			   text.setText("��ȫ�Զ���Toast");
			   Toast toast = new Toast(context.getApplicationContext());
			   toast.setGravity(Gravity.RIGHT | Gravity.TOP, 12, 40);
			   toast.setDuration(Toast.LENGTH_LONG);
			   toast.setView(layout);
			   toast.show();
			
			*/
			//����������� ʧ��
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			//��С
			TextView textView = new TextView(context);
			
			
			
			textView.setText(sb.toString());
			// �����ı���������Ĵ�С����ɫ
			textView.setTextSize(40);
			//textView.setTextColor(Color.MAGENTA);	//��ɫ
			
			//5000����ʱ�����
			Toast toast = Toast.makeText(context,sb.toString(), 20000);
			toast.setView(textView);
			
			
			
			
			toast.setGravity(Gravity.CENTER, 0, 0);
			toast.show();
			//��С
			
			
			
			
			
			
			
			
			
			
			/*
			Toast toast=new Toast(this);

	           toast.setView(view);

	           //����view,����ʾtoast.xml������

	           TextView tv=(TextView)view.findViewById(R.id.tv1);

	           tv.setText("Toast��ʾView����");

	           //�޸�TextView�������

	           toast.setDuration(Toast.LENGTH_SHORT);

	           //������ʾʱ�䣬��ʱ��Toast.LENGTH_LONG����ʱ��ΪToast.LENGTH_SHORT,�������Լ��༭

	           toast.show();

			 	*/
			
			
			
			
			/*
			 Intent activityIntent = new Intent();
			 intent.setClass(Context packageContext, ToastTest) ; 
			 
	        Intent activityIntent = new Intent(context, ToastTest.class);    
	        //  Ҫ����Service������Activity�������������±�־�������ѵĲ�֪����㣩    
	        activityIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);    
	        context.startActivity(activityIntent);  
			*/
			
			//ToastTest.toast.show();

			
		}	
	}
	
	/*
	public static class ToastTest extends Activity
	{
		public static Toast toast;

		//@Override
		public void onCreate(Bundle savedInstanceState)
		{
			super.onCreate(savedInstanceState);
			setContentView(R.layout.main);
		
		
			
				
					// ����һ��Toast��ʾ��Ϣ
					toast = new Toast(ToastTest.this);
					// ����Toast����ʾλ��
					toast.setGravity(Gravity.CENTER, 0, 0);
					// ����һ��ImageView
					ImageView image = new ImageView(ToastTest.this);
					image.setImageResource(R.drawable.app_icon);
					// ����һ��LinearLayout����
					LinearLayout ll = new LinearLayout(ToastTest.this);
					// ��LinearLayout�����ͼƬ��ԭ�е�View
					ll.addView(image);
					// ����һ��ImageView
					TextView textView = new TextView(ToastTest.this);
					textView.setText("��ͼƬ����ʾ��");
					// �����ı���������Ĵ�С����ɫ
					textView.setTextSize(30);
					textView.setTextColor(Color.MAGENTA);
					ll.addView(textView);
					 //����Toast��ʾ�Զ���View				
					toast.setView(ll);
					// ����Toast����ʾʱ��
					toast.setDuration(Toast.LENGTH_LONG);
					//toast.show();
				
					
		}
	}
	*/
}

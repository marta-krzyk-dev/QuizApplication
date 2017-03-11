using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
  
  public ref class YourForm : public System::Windows::Forms::Form
	{
  //...
    private:
		
		System::Windows::Forms::Timer^  timer;
    System::Windows::Forms::Panel^  clock_panel;
    
		int width, Y_point;
		int time_in_seconds;
		float angle;
		float angle_increase;
		static Drawing::Font^ draw_font;
		System::Drawing::Rectangle rect;
		System::Drawing::Graphics^	g;

		static SolidBrush^ green_brush = gcnew SolidBrush(Color::LimeGreen);
		static SolidBrush^ yellow_brush = gcnew SolidBrush(Color::FromArgb(227,217,15));
		static SolidBrush^ orange_brush = gcnew SolidBrush(Color::DarkOrange);
		static SolidBrush^ red_brush = gcnew SolidBrush(Color::Red);
		static SolidBrush^ draw_brush = gcnew SolidBrush(Color::White);
		static Pen^ black_pen = gcnew Pen( Color::Black, 0.0f );
	
		PointF text_start_point;
		SizeF  text_size;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
        // ...
      this->panelZegar = (gcnew System::Windows::Forms::Panel());
        // ...
      this->timer = (gcnew System::Windows::Forms::Timer(this->components));
      this->timer->Interval = 1000;
	    this->timer->Tick += gcnew System::EventHandler(this, &YourForm::timer_Tick);
    }
#pragma endregion

private: System::Void timer_Tick(System::Object^  sender, System::EventArgs^  e) {

	
				if (time_in_seconds <= 0) //Time is up
					timer->Stop();
					return;

				//Time is running

				 --time_in_seconds; //Decrease the amount of seconds left
				 angle += angle_increase; //Increase the angle of pie

				//Clean the previous drawing
				g->Clear(clock_panel->BackColor); 

				//Draw a black clock face
				g->DrawEllipse(black_pen, rect);

				//Draw a pie, the colour depends on the amount of seconds left
				if (time_in_seconds > 9) //Over 9 seconds left
					g->FillPie( green_brush, rect, 270.0F, angle); //Draw a green pie
				else
					if (time_in_seconds > 6) //7-9 seconds left
						g->FillPie( yellow_brush, rect, 270.0F, angle); //Draw a yellow pie
					else
						if (time_in_seconds > 3) //4-6 seconds left
							g->FillPie( orange_brush, rect, 270.0F, angle);//Draw an orange pie
						else	//0-3 seconds left
							g->FillPie( red_brush, rect, 270.0F, angle); //Draw a red pie

				//Calculate size of text, e.g. "14"
				text_size = g->MeasureString( time_in_seconds.ToString(), draw_font );

				//Calculate the left, upper corner of the centered text
				text_start_point = PointF((width - text_size.Width)/2, Y_point);

				//Draw the text
				g->DrawString(time_in_seconds.ToString(), draw_font, draw_brush, text_start_point);		
	
}
}

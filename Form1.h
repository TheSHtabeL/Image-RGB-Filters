#pragma once

namespace Lab04_1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		OpenFileDialog^ OpenFile;
	private: System::Windows::Forms::ToolStripMenuItem^  HistAll;
	public: 
		int HistFlag;
		int ImageFlag;
		int FilterFlag;
		Bitmap^ ImageBitmap;
		Bitmap^ WorkBitmap;
		Bitmap^ HistBitmap;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  ColorIndicator;

	private: System::Windows::Forms::ToolStripMenuItem^  фильтрToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  цветToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  градацииСерогоToolStripMenuItem;

	public: 
	private: System::Windows::Forms::ToolStripMenuItem^  IOblack;
	public: 
		Form1(void)
		{
			InitializeComponent();
			OpenFile = gcnew OpenFileDialog();
		}
		void Computation()
		{
			WorkBitmap = gcnew Bitmap(520,440);
			Color PixelColor;
			//Подготовливаем буферы
			array<array<int>^>^ BufferRed = gcnew array<array<int>^>(512);
			for(int i=0; i<512; i++)
			{
				BufferRed[i] = gcnew array<int>(440);
			}
			array<array<int>^>^ BufferGreen = gcnew array<array<int>^>(512);
			for(int i=0; i<512; i++)
			{
				BufferGreen[i] = gcnew array<int>(440);
			}
			array<array<int>^>^ BufferBlue = gcnew array<array<int>^>(512);
			for(int i=0; i<512; i++)
			{
				BufferBlue[i] = gcnew array<int>(440);
			}
			array<array<int>^>^ BufferBlack = gcnew array<array<int>^>(512);
			for(int i=0; i<512; i++)
			{
				BufferBlack[i] = gcnew array<int>(440);
			}
			//Заполняем буферы информацией
			for(int i=0; i<512; i++)
			{
				for(int j=0; j<440; j++)
				{
					BufferRed[i][j] = ImageBitmap->GetPixel(i,j).R;
					BufferGreen[i][j] = ImageBitmap->GetPixel(i,j).G;
					BufferBlue[i][j] = ImageBitmap->GetPixel(i,j).B;
					BufferBlack[i][j] = (BufferRed[i][j] + BufferGreen[i][j] + BufferBlue[i][j]) / 3;
				}
			}
			//Обрабатываем вывод изображения
			switch(ImageFlag)
			{
			case 0:
				for(int i=0; i<512; i++)
				{
					for(int j=0; j<440; j++)
					{
						WorkBitmap->SetPixel(i,j,PixelColor.FromArgb(BufferRed[i][j],BufferGreen[i][j],BufferBlue[i][j]));
					}
				}
				PictureWindow->Image = WorkBitmap;
				break;
			case 1:
				for(int i=0; i<512; i++)
				{
					for(int j=0; j<440; j++)
					{
						if(FilterFlag)
						{
							WorkBitmap->SetPixel(i,j,PixelColor.FromArgb(BufferRed[i][j],BufferRed[i][j],BufferRed[i][j]));
						}else{
							WorkBitmap->SetPixel(i,j,PixelColor.FromArgb(BufferRed[i][j],0,0));
						}
					}
				}
				PictureWindow->Image = WorkBitmap;
				break;
			case 2:
				for(int i=0; i<512; i++)
				{
					for(int j=0; j<440; j++)
					{
						if(FilterFlag)
						{
							WorkBitmap->SetPixel(i,j,PixelColor.FromArgb(BufferGreen[i][j],BufferGreen[i][j],BufferGreen[i][j]));
						}else{
							WorkBitmap->SetPixel(i,j,PixelColor.FromArgb(0,BufferGreen[i][j],0));
						}
					}
				}
				PictureWindow->Image = WorkBitmap;
				break;
			case 3:
				for(int i=0; i<512; i++)
				{
					for(int j=0; j<440; j++)
					{
						if(FilterFlag)
						{						
							WorkBitmap->SetPixel(i,j,PixelColor.FromArgb(BufferBlue[i][j],BufferBlue[i][j],BufferBlue[i][j]));
						}else{
							WorkBitmap->SetPixel(i,j,PixelColor.FromArgb(0,0,BufferBlue[i][j]));
						}
					}
				}
				PictureWindow->Image = WorkBitmap;
				break;
			case 4:
				for(int i=0; i<512; i++)
				{
					for(int j=0; j<440; j++)
					{
						WorkBitmap->SetPixel(i,j,PixelColor.FromArgb(BufferBlack[i][j],BufferBlack[i][j],BufferBlack[i][j]));
					}
				}
				PictureWindow->Image = WorkBitmap;
				break;
			}
			//Готовим гистограммы
			HistBitmap = gcnew Bitmap(256,440);
			array<int>^ TimeHist = gcnew array<int>(256);
			for(int i=0; i<256; i++)
			{
				TimeHist[i] = 0;
			}
			switch(HistFlag)
			{
			case 1:
				//Подсчитываем количество пикселей текущей яркости
				for(int i=0; i<512; i++)
				{
					for(int j=0; j<440; j++)
					{
						TimeHist[BufferRed[i][j]]++;
					}
				}
				for(int i=0; i<256; i++)
				{
					TimeHist[i] /= 10;
				}
				//Заполняем Bitmap
				for(int i=0; i<256; i++)
				{
					int k=0;
					for(int j=439; j > 0; j--)
					{
						HistBitmap->SetPixel(i,j,PixelColor.FromArgb(i,0,0));
						k++;
						if(k>TimeHist[i])
						{
							j=0;
						}
					}
				}
				HistWindow->Image = HistBitmap;
				break;
			case 2:
				//Подсчитываем количество пикселей текущей яркости
				for(int i=0; i<512; i++)
				{
					for(int j=0; j<440; j++)
					{
						TimeHist[BufferGreen[i][j]]++;
					}
				}
				for(int i=0; i<256; i++)
				{
					TimeHist[i] /= 10;
				}
				//Заполняем Bitmap
				for(int i=0; i<256; i++)
				{
					int k=0;
					for(int j=439; j > 0; j--)
					{
						HistBitmap->SetPixel(i,j,PixelColor.FromArgb(0,i,0));
						k++;
						if(k>TimeHist[i])
						{
							j=0;
						}
					}
				}
				HistWindow->Image = HistBitmap;
				break;
			case 3:
				//Подсчитываем количество пикселей текущей яркости
				for(int i=0; i<512; i++)
				{
					for(int j=0; j<440; j++)
					{
						TimeHist[BufferBlue[i][j]]++;
					}
				}
				for(int i=0; i<256; i++)
				{
					TimeHist[i] /= 10;
				}
				//Заполняем Bitmap
				for(int i=0; i<256; i++)
				{
					int k=0;
					for(int j=439; j > 0; j--)
					{
						HistBitmap->SetPixel(i,j,PixelColor.FromArgb(0,0,i));
						k++;
						if(k>TimeHist[i])
						{
							j=0;
						}
					}
				}
				HistWindow->Image = HistBitmap;
				break;
			case 4:
				//Подсчитываем количество пикселей текущей яркости
				for(int i=0; i<512; i++)
				{
					for(int j=0; j<440; j++)
					{
						TimeHist[BufferBlack[i][j]]++;
					}
				}
				for(int i=0; i<256; i++)
				{
					TimeHist[i] /= 10;
				}
				//Заполняем Bitmap
				for(int i=0; i<256; i++)
				{
					int k=0;
					for(int j=439; j > 0; j--)
					{
						HistBitmap->SetPixel(i,j,PixelColor.FromArgb(i,i,i));
						k++;
						if(k>TimeHist[i])
						{
							j=0;
						}
					}
				}
				HistWindow->Image = HistBitmap;
				break;
			}
		}
		

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  ImageMenu;
	protected: 

	private: System::Windows::Forms::ToolStripMenuItem^  LoadFile;
	private: System::Windows::Forms::ToolStripMenuItem^  OutputImage;
	private: System::Windows::Forms::ToolStripMenuItem^  IOoriginal;
	private: System::Windows::Forms::ToolStripMenuItem^  IOred;
	private: System::Windows::Forms::ToolStripMenuItem^  IOgreen;
	private: System::Windows::Forms::ToolStripMenuItem^  IOblue;
	private: System::Windows::Forms::ToolStripMenuItem^  HistMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  HistRed;
	private: System::Windows::Forms::ToolStripMenuItem^  HistGreen;
	private: System::Windows::Forms::ToolStripMenuItem^  HistBlue;
	private: System::Windows::Forms::PictureBox^  PictureWindow;
	private: System::Windows::Forms::PictureBox^  HistWindow;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ImageMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LoadFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->OutputImage = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->IOoriginal = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->IOred = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->IOgreen = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->IOblue = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->IOblack = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HistMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HistRed = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HistGreen = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HistBlue = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->HistAll = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->фильтрToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->цветToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->градацииСерогоToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PictureWindow = (gcnew System::Windows::Forms::PictureBox());
			this->HistWindow = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->ColorIndicator = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PictureWindow))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->HistWindow))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->ImageMenu, this->HistMenu, 
				this->фильтрToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(972, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ImageMenu
			// 
			this->ImageMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->LoadFile, 
				this->OutputImage});
			this->ImageMenu->Name = L"ImageMenu";
			this->ImageMenu->Size = System::Drawing::Size(95, 20);
			this->ImageMenu->Text = L"Изображение";
			this->ImageMenu->Click += gcnew System::EventHandler(this, &Form1::данныеToolStripMenuItem_Click);
			// 
			// LoadFile
			// 
			this->LoadFile->Name = L"LoadFile";
			this->LoadFile->Size = System::Drawing::Size(205, 22);
			this->LoadFile->Text = L"Загрузить изображение";
			this->LoadFile->Click += gcnew System::EventHandler(this, &Form1::загрузитьФайлToolStripMenuItem_Click);
			// 
			// OutputImage
			// 
			this->OutputImage->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->IOoriginal, 
				this->IOred, this->IOgreen, this->IOblue, this->IOblack});
			this->OutputImage->Name = L"OutputImage";
			this->OutputImage->Size = System::Drawing::Size(205, 22);
			this->OutputImage->Text = L"Вывод на экран";
			// 
			// IOoriginal
			// 
			this->IOoriginal->Name = L"IOoriginal";
			this->IOoriginal->Size = System::Drawing::Size(180, 22);
			this->IOoriginal->Text = L"Оригинальное";
			this->IOoriginal->Click += gcnew System::EventHandler(this, &Form1::IOoriginal_Click);
			// 
			// IOred
			// 
			this->IOred->Name = L"IOred";
			this->IOred->Size = System::Drawing::Size(180, 22);
			this->IOred->Text = L"Градации красного";
			this->IOred->Click += gcnew System::EventHandler(this, &Form1::IOred_Click);
			// 
			// IOgreen
			// 
			this->IOgreen->Name = L"IOgreen";
			this->IOgreen->Size = System::Drawing::Size(180, 22);
			this->IOgreen->Text = L"Градации зелёного";
			this->IOgreen->Click += gcnew System::EventHandler(this, &Form1::IOgreen_Click);
			// 
			// IOblue
			// 
			this->IOblue->Name = L"IOblue";
			this->IOblue->Size = System::Drawing::Size(180, 22);
			this->IOblue->Text = L"Градации синего";
			this->IOblue->Click += gcnew System::EventHandler(this, &Form1::IOblue_Click);
			// 
			// IOblack
			// 
			this->IOblack->Name = L"IOblack";
			this->IOblack->Size = System::Drawing::Size(180, 22);
			this->IOblack->Text = L"Градации яркости";
			this->IOblack->Click += gcnew System::EventHandler(this, &Form1::IOblack_Click);
			// 
			// HistMenu
			// 
			this->HistMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->HistRed, this->HistGreen, 
				this->HistBlue, this->HistAll});
			this->HistMenu->Name = L"HistMenu";
			this->HistMenu->Size = System::Drawing::Size(95, 20);
			this->HistMenu->Text = L"Гистограммы";
			// 
			// HistRed
			// 
			this->HistRed->Name = L"HistRed";
			this->HistRed->Size = System::Drawing::Size(152, 22);
			this->HistRed->Text = L"Красная";
			this->HistRed->Click += gcnew System::EventHandler(this, &Form1::HistRed_Click);
			// 
			// HistGreen
			// 
			this->HistGreen->Name = L"HistGreen";
			this->HistGreen->Size = System::Drawing::Size(152, 22);
			this->HistGreen->Text = L"Зелёная";
			this->HistGreen->Click += gcnew System::EventHandler(this, &Form1::HistGreen_Click);
			// 
			// HistBlue
			// 
			this->HistBlue->Name = L"HistBlue";
			this->HistBlue->Size = System::Drawing::Size(152, 22);
			this->HistBlue->Text = L"Синяя";
			this->HistBlue->Click += gcnew System::EventHandler(this, &Form1::HistBlue_Click);
			// 
			// HistAll
			// 
			this->HistAll->Name = L"HistAll";
			this->HistAll->Size = System::Drawing::Size(152, 22);
			this->HistAll->Text = L"Общая";
			this->HistAll->Click += gcnew System::EventHandler(this, &Form1::HistAll_Click);
			// 
			// фильтрToolStripMenuItem
			// 
			this->фильтрToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->цветToolStripMenuItem, 
				this->градацииСерогоToolStripMenuItem});
			this->фильтрToolStripMenuItem->Name = L"фильтрToolStripMenuItem";
			this->фильтрToolStripMenuItem->Size = System::Drawing::Size(60, 20);
			this->фильтрToolStripMenuItem->Text = L"Фильтр";
			// 
			// цветToolStripMenuItem
			// 
			this->цветToolStripMenuItem->Name = L"цветToolStripMenuItem";
			this->цветToolStripMenuItem->Size = System::Drawing::Size(183, 22);
			this->цветToolStripMenuItem->Text = L"RGB-составляющая";
			this->цветToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::цветToolStripMenuItem_Click);
			// 
			// градацииСерогоToolStripMenuItem
			// 
			this->градацииСерогоToolStripMenuItem->Name = L"градацииСерогоToolStripMenuItem";
			this->градацииСерогоToolStripMenuItem->Size = System::Drawing::Size(183, 22);
			this->градацииСерогоToolStripMenuItem->Text = L"Градации серого";
			this->градацииСерогоToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::градацииСерогоToolStripMenuItem_Click);
			// 
			// PictureWindow
			// 
			this->PictureWindow->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->PictureWindow->Location = System::Drawing::Point(60, 98);
			this->PictureWindow->Name = L"PictureWindow";
			this->PictureWindow->Size = System::Drawing::Size(512, 440);
			this->PictureWindow->TabIndex = 1;
			this->PictureWindow->TabStop = false;
			// 
			// HistWindow
			// 
			this->HistWindow->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->HistWindow->Location = System::Drawing::Point(648, 98);
			this->HistWindow->Name = L"HistWindow";
			this->HistWindow->Size = System::Drawing::Size(255, 440);
			this->HistWindow->TabIndex = 2;
			this->HistWindow->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label1->Location = System::Drawing::Point(221, 49);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(187, 31);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Изображение";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20));
			this->label2->Location = System::Drawing::Point(689, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(178, 31);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Гистограмма";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->label3->Location = System::Drawing::Point(644, 541);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(20, 24);
			this->label3->TabIndex = 5;
			this->label3->Text = L"0";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// ColorIndicator
			// 
			this->ColorIndicator->AutoSize = true;
			this->ColorIndicator->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->ColorIndicator->Location = System::Drawing::Point(884, 541);
			this->ColorIndicator->Name = L"ColorIndicator";
			this->ColorIndicator->Size = System::Drawing::Size(40, 24);
			this->ColorIndicator->TabIndex = 6;
			this->ColorIndicator->Text = L"255";
			this->ColorIndicator->Click += gcnew System::EventHandler(this, &Form1::ColorIndicator_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(972, 590);
			this->Controls->Add(this->ColorIndicator);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->HistWindow);
			this->Controls->Add(this->PictureWindow);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Image RGB Filters";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PictureWindow))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->HistWindow))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void данныеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void загрузитьФайлToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Выбрать файл в проводнике
				 ImageFlag = 0;
				 HistFlag = 0;
				 FilterFlag = 0;
				 OpenFile->Filter = "JPG (*.jpg)|*.jpg|BMP (*.bmp)|*.bmp|PNG (*.png)|*.*|All files (*.*)|*.*";
				 if (OpenFile->ShowDialog() ==System::Windows::Forms::DialogResult::OK)
				 {
					 ImageBitmap = gcnew Bitmap(OpenFile->FileName);
					 PictureWindow->Image = ImageBitmap;
					 Computation();
				 }
				 
			 }
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void HistRed_Click(System::Object^  sender, System::EventArgs^  e) {
			 HistFlag = 1;
			 Computation();
		 }
private: System::Void HistGreen_Click(System::Object^  sender, System::EventArgs^  e) {
			 HistFlag = 2;
			 Computation();
		 }
private: System::Void HistBlue_Click(System::Object^  sender, System::EventArgs^  e) {
			 HistFlag = 3;
			 Computation();
		 }
private: System::Void HistAll_Click(System::Object^  sender, System::EventArgs^  e) {
			 HistFlag = 4;
			 Computation();
		 }
private: System::Void IOoriginal_Click(System::Object^  sender, System::EventArgs^  e) {
			 ImageFlag = 0;
			 Computation();
		 }
private: System::Void IOred_Click(System::Object^  sender, System::EventArgs^  e) {
			 ImageFlag = 1;
			 Computation();
		 }
private: System::Void IOgreen_Click(System::Object^  sender, System::EventArgs^  e) {
			 ImageFlag = 2;
			 Computation();
		 }
private: System::Void IOblue_Click(System::Object^  sender, System::EventArgs^  e) {
			 ImageFlag = 3;
			 Computation();
		 }
private: System::Void IOblack_Click(System::Object^  sender, System::EventArgs^  e) {
			 ImageFlag = 4;
			 Computation();
		 }
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void цветToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 FilterFlag = 0;
			 Computation();
		 }
private: System::Void градацииСерогоToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 FilterFlag = 1;
			 Computation();
		 }
private: System::Void ColorIndicator_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}


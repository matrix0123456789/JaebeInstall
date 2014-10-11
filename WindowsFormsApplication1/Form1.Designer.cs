namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.FolSrc = new System.Windows.Forms.TextBox();
            this.FolDoc = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.Kompr = new System.Windows.Forms.TextBox();
            this.Wersja = new System.Windows.Forms.TextBox();
            this.Autor = new System.Windows.Forms.TextBox();
            this.Licencja = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.label8 = new System.Windows.Forms.Label();
            this.FolDom = new System.Windows.Forms.TextBox();
            this.InnyFolDom = new System.Windows.Forms.CheckBox();
            this.label6 = new System.Windows.Forms.Label();
            this.coIleDzieli = new System.Windows.Forms.TextBox();
            this.checkObrazek = new System.Windows.Forms.CheckBox();
            this.ObrPole = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.czyKompresja = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // FolSrc
            // 
            this.FolSrc.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FolSrc.Location = new System.Drawing.Point(161, 6);
            this.FolSrc.Name = "FolSrc";
            this.FolSrc.Size = new System.Drawing.Size(536, 20);
            this.FolSrc.TabIndex = 0;
            this.FolSrc.Text = "C:\\";
            // 
            // FolDoc
            // 
            this.FolDoc.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FolDoc.Location = new System.Drawing.Point(161, 36);
            this.FolDoc.Name = "FolDoc";
            this.FolDoc.Size = new System.Drawing.Size(536, 20);
            this.FolDoc.TabIndex = 0;
            this.FolDoc.Text = "C:\\";
            // 
            // button1
            // 
            this.button1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button1.Location = new System.Drawing.Point(9, 385);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(146, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Generuj";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(82, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Folder źródłowy";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 39);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(149, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Folder do zapisania instalatora";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 84);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(40, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "Nazwa";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 110);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(40, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "Wersja";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 136);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(32, 13);
            this.label5.TabIndex = 5;
            this.label5.Text = "Autor";
            // 
            // Kompr
            // 
            this.Kompr.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Kompr.Location = new System.Drawing.Point(161, 237);
            this.Kompr.Name = "Kompr";
            this.Kompr.Size = new System.Drawing.Size(455, 20);
            this.Kompr.TabIndex = 7;
            this.Kompr.Text = "64";
            this.Kompr.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // Wersja
            // 
            this.Wersja.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Wersja.Location = new System.Drawing.Point(161, 107);
            this.Wersja.Name = "Wersja";
            this.Wersja.Size = new System.Drawing.Size(536, 20);
            this.Wersja.TabIndex = 8;
            this.Wersja.Text = "1.0";
            // 
            // Autor
            // 
            this.Autor.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Autor.Location = new System.Drawing.Point(161, 133);
            this.Autor.Name = "Autor";
            this.Autor.Size = new System.Drawing.Size(536, 20);
            this.Autor.TabIndex = 9;
            this.Autor.Text = "Jaebe Studio";
            this.Autor.TextChanged += new System.EventHandler(this.Autor_TextChanged);
            // 
            // Licencja
            // 
            this.Licencja.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Licencja.Location = new System.Drawing.Point(161, 289);
            this.Licencja.Multiline = true;
            this.Licencja.Name = "Licencja";
            this.Licencja.Size = new System.Drawing.Size(536, 119);
            this.Licencja.TabIndex = 10;
            this.Licencja.Text = "Zabrania się kopiowania etc.";
            // 
            // textBox1
            // 
            this.textBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox1.Location = new System.Drawing.Point(161, 159);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(536, 20);
            this.textBox1.TabIndex = 11;
            this.textBox1.Text = "Start.exe";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 162);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(105, 13);
            this.label7.TabIndex = 12;
            this.label7.Text = "Plik do uruchomienia";
            // 
            // progressBar1
            // 
            this.progressBar1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.progressBar1.Location = new System.Drawing.Point(9, 414);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(688, 16);
            this.progressBar1.TabIndex = 13;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 214);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(99, 13);
            this.label8.TabIndex = 14;
            this.label8.Text = "Co ile bajtów dzielić";
            // 
            // FolDom
            // 
            this.FolDom.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FolDom.Enabled = false;
            this.FolDom.Location = new System.Drawing.Point(161, 185);
            this.FolDom.Name = "FolDom";
            this.FolDom.Size = new System.Drawing.Size(536, 20);
            this.FolDom.TabIndex = 15;
            this.FolDom.Text = "C:\\Program Files";
            // 
            // InnyFolDom
            // 
            this.InnyFolDom.AutoSize = true;
            this.InnyFolDom.Location = new System.Drawing.Point(9, 187);
            this.InnyFolDom.Name = "InnyFolDom";
            this.InnyFolDom.Size = new System.Drawing.Size(121, 17);
            this.InnyFolDom.TabIndex = 16;
            this.InnyFolDom.Text = "Inny folder domyślny";
            this.InnyFolDom.UseVisualStyleBackColor = true;
            this.InnyFolDom.CheckedChanged += new System.EventHandler(this.InnyFolDom_CheckedChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 292);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(47, 13);
            this.label6.TabIndex = 17;
            this.label6.Text = "Licencja";
            // 
            // coIleDzieli
            // 
            this.coIleDzieli.Location = new System.Drawing.Point(161, 211);
            this.coIleDzieli.Name = "coIleDzieli";
            this.coIleDzieli.Size = new System.Drawing.Size(536, 20);
            this.coIleDzieli.TabIndex = 18;
            this.coIleDzieli.Text = "1000000000";
            // 
            // checkObrazek
            // 
            this.checkObrazek.AutoSize = true;
            this.checkObrazek.Location = new System.Drawing.Point(2, 265);
            this.checkObrazek.Name = "checkObrazek";
            this.checkObrazek.Size = new System.Drawing.Size(66, 17);
            this.checkObrazek.TabIndex = 19;
            this.checkObrazek.Text = "Obrazek";
            this.checkObrazek.UseVisualStyleBackColor = true;
            this.checkObrazek.CheckedChanged += new System.EventHandler(this.checkObrazek_CheckedChanged);
            // 
            // ObrPole
            // 
            this.ObrPole.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ObrPole.Enabled = false;
            this.ObrPole.Location = new System.Drawing.Point(161, 263);
            this.ObrPole.Name = "ObrPole";
            this.ObrPole.Size = new System.Drawing.Size(441, 20);
            this.ObrPole.TabIndex = 20;
            // 
            // button2
            // 
            this.button2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.button2.Location = new System.Drawing.Point(608, 262);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(89, 20);
            this.button2.TabIndex = 21;
            this.button2.Text = "Wybierz plik";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button3.Location = new System.Drawing.Point(9, 356);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(146, 23);
            this.button3.TabIndex = 22;
            this.button3.Text = "Testuj";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // textBox2
            // 
            this.textBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox2.Location = new System.Drawing.Point(161, 77);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(536, 20);
            this.textBox2.TabIndex = 23;
            this.textBox2.Text = "Program";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 240);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(128, 13);
            this.label9.TabIndex = 24;
            this.label9.Text = "Ustawienie kompresji (kB)";
            // 
            // czyKompresja
            // 
            this.czyKompresja.AutoSize = true;
            this.czyKompresja.Checked = true;
            this.czyKompresja.CheckState = System.Windows.Forms.CheckState.Checked;
            this.czyKompresja.Location = new System.Drawing.Point(622, 239);
            this.czyKompresja.Name = "czyKompresja";
            this.czyKompresja.Size = new System.Drawing.Size(75, 17);
            this.czyKompresja.TabIndex = 25;
            this.czyKompresja.Text = "Kompresuj";
            this.czyKompresja.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(709, 442);
            this.Controls.Add(this.czyKompresja);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.ObrPole);
            this.Controls.Add(this.checkObrazek);
            this.Controls.Add(this.coIleDzieli);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.InnyFolDom);
            this.Controls.Add(this.FolDom);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.Licencja);
            this.Controls.Add(this.Autor);
            this.Controls.Add(this.Wersja);
            this.Controls.Add(this.Kompr);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.FolDoc);
            this.Controls.Add(this.FolSrc);
            this.MinimumSize = new System.Drawing.Size(305, 263);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox FolSrc;
        private System.Windows.Forms.TextBox FolDoc;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox Kompr;
        private System.Windows.Forms.TextBox Wersja;
        private System.Windows.Forms.TextBox Autor;
        private System.Windows.Forms.TextBox Licencja;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox FolDom;
        private System.Windows.Forms.CheckBox InnyFolDom;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox coIleDzieli;
        private System.Windows.Forms.CheckBox checkObrazek;
        private System.Windows.Forms.TextBox ObrPole;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.CheckBox czyKompresja;
    }
}


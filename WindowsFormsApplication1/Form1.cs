using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public static int Progress = 0, ProgressMax = 0;
        public Form1()
        {
            InitializeComponent();
            odświerzanie = new System.Threading.Timer((a) =>
            {
                try { progressBar1.BeginInvoke(new InvokeDelegate(InvokeMethod)); }
                catch { }
            }, null, 0, 10);
            InnyFolDom_CheckedChanged(null, null);

        }

        private void InvokeMethod()
        {
            progressBar1.Maximum = ProgressMax;
            progressBar1.Value = Progress;
        }
        public delegate void InvokeDelegate();
        private void button1_Click(object sender, EventArgs e)
        {

            var Proje = new ProjektInstalatora();
            Proje.folderŹródłowy = FolSrc.Text;
            Proje.folderDocelowy = FolDoc.Text;
            Proje.nazwa = Nazwa.Text;
            Proje.wersja = Wersja.Text;
            Proje.autor = Autor.Text;
            Proje.licencja = Licencja.Text;
            InnyFolDom_CheckedChanged(null, null);
            Proje.FolderDom = FolDom.Text;
            var wątek = new Thread((o) =>
            {

                Proje.zapisz();
                MessageBox.Show("Gotowe!");
            });
            wątek.Start();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            InnyFolDom_CheckedChanged(null, null);
        }


        public System.Threading.Timer odświerzanie { get; set; }

        private void InnyFolDom_CheckedChanged(object sender, EventArgs e)
        {
            if (InnyFolDom.Checked)
                FolDom.Enabled = true;
            else
            {
                FolDom.Enabled = false;
                FolDom.Text = "C:\\Program Files\\" + Autor.Text + "\\" + Nazwa.Text;
            }
        }

        private void Autor_TextChanged(object sender, EventArgs e)
        {
            InnyFolDom_CheckedChanged(null, null);
        }

    }
}

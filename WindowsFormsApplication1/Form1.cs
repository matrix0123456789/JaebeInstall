using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
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
            if (czyKompresja.Checked)
                Proje.kompresja = Kompresja.Zlib;
            else
                Proje.kompresja = Kompresja.Brak;
            Proje.folderDocelowy = FolDoc.Text;
            Proje.plikWykonywalny = textBox1.Text;
            Proje.nazwa = textBox2.Text;
            Proje.wersja = Wersja.Text;
            Proje.autor = Autor.Text;
            Proje.licencja = Licencja.Text;
            try{
                Proje.dzielkompr = Int32.Parse(Kompr.Text) * 1024;
            }
                catch{}
            if (checkObrazek.Checked)
                Proje.Obrazek = ObrPole.Text;
            try
            {
                Proje.coIleDziel = ulong.Parse(coIleDzieli.Text);
            }
            catch { Proje.coIleDziel = long.MaxValue; }
            InnyFolDom_CheckedChanged(null, null);
            Proje.FolderDom = FolDom.Text;
            var wątek = new Thread((o) =>
            {
                DateTime start = DateTime.Now;
                Proje.zapisz(true);
                MessageBox.Show("Gotowe!\r\nCzas: "+(DateTime.Now-start).TotalSeconds+"s");
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
                FolDom.Text = "C:\\Program Files\\" + Autor.Text + "\\" + textBox2.Text;
            }
        }

        private void Autor_TextChanged(object sender, EventArgs e)
        {
            InnyFolDom_CheckedChanged(null, null);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            OpenFileDialog d = new OpenFileDialog();
            d.Filter = "Obrazek|*.bmp";
            d.ShowDialog();
            ObrPole.Text = d.FileName;
            if (sender != null && ObrPole.Text != "")
                checkObrazek.Checked = true;
        }

        private void checkObrazek_CheckedChanged(object sender, EventArgs e)
        {
            if ((sender as CheckBox).Checked && ObrPole.Text == "")
                button2_Click(null, null);
            ObrPole.Enabled = (sender as CheckBox).Checked;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                var d = new DirectoryInfo(System.IO.Path.GetTempPath() + "JaebeInstallTest");
                d.Delete(true);
            }
            catch { }
            Application.Exit();
            
        }

        private void button3_Click(object sender, EventArgs e)
        {
            var Proje = new ProjektInstalatora();
            Proje.folderŹródłowy = FolSrc.Text;
            Proje.plikWykonywalny = textBox1.Text;
            Proje.folderDocelowy = System.IO.Path.GetTempPath()+"JaebeInstallTest";
            Proje.nazwa = textBox2.Text;
            Proje.wersja = Wersja.Text;
            Proje.autor = Autor.Text;
            Proje.licencja = Licencja.Text;
            if (checkObrazek.Checked)
                Proje.Obrazek = ObrPole.Text;
            InnyFolDom_CheckedChanged(null, null);
            Proje.FolderDom = FolDom.Text;
            var wątek = new Thread((o) =>
            {

                Proje.zapisz(false);
                Process.Start(System.IO.Path.GetTempPath() + "JaebeInstallTest\\install.exe");
            });
            wątek.Start();
        }

    }
}

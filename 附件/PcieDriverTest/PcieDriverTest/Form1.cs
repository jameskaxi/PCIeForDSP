using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using pcieDriverHelper;
using System.IO;
using System.Diagnostics;
using System.Collections;

namespace PcieDriverTest
{
    public partial class Form1 : Form
    {
        private DmaTransfer dmaTransfer = new DmaTransfer();
        private Stopwatch swDmaTime = new Stopwatch();  // zhu 计时器
        private double dmaSpeedMB = 0;
        private int dmaCompleted = 0;

        public enum InputMod { Int, UInt, Float, UFloat, Hex, NewHex };

        /// <summary>
        /// 输入限制
        /// </summary>
        static public void InputLimit(TextBox textBox, KeyPressEventArgs e, InputMod inputMod)
        {
            string strStart, strEnd;

            e.Handled = false;
            if (e.KeyChar == '\b')
                return;

            strStart = textBox.Text.Substring(0, textBox.SelectionStart);
            strEnd = textBox.Text.Substring(textBox.SelectionStart + textBox.SelectionLength,
                textBox.Text.Length - textBox.SelectionStart - textBox.SelectionLength);

            switch (inputMod)
            {
                case InputMod.Int:
                    {
                        int data;

                        if (!Char.IsDigit(e.KeyChar) && e.KeyChar != '-')
                        {
                            e.Handled = true;
                            return;
                        }

                        if (!int.TryParse(strStart + e.KeyChar + strEnd, out data) && (strStart + strEnd) != "")
                        {
                            e.Handled = true;
                            return;
                        }
                        break;
                    }
                case InputMod.UInt:
                    {
                        if (!Char.IsDigit(e.KeyChar))
                        {
                            e.Handled = true;
                            return;
                        }
                        break;
                    }
                case InputMod.Float:
                    {
                        float data;

                        if (!Char.IsDigit(e.KeyChar) && e.KeyChar != '-' && e.KeyChar != '.')
                        {
                            e.Handled = true;
                            return;
                        }

                        if (!float.TryParse(strStart + e.KeyChar + strEnd, out data)
                            && (strStart + strEnd) != ""
                            && (strStart + e.KeyChar + strEnd) != "-.")
                        {
                            e.Handled = true;
                            return;
                        }
                        break;
                    }
                case InputMod.UFloat:
                    {
                        float data;

                        if (!Char.IsDigit(e.KeyChar) && e.KeyChar != '.')
                        {
                            e.Handled = true;
                            return;
                        }

                        if (!float.TryParse(strStart + e.KeyChar + strEnd, out data)
                              && (strStart + strEnd) != "")
                        {
                            e.Handled = true;
                            return;
                        }
                        break;
                    }
                case InputMod.Hex:
                    {
                        if (!Char.IsDigit(e.KeyChar) 
                            && !(e.KeyChar >= 'a' && e.KeyChar <= 'f')
                            && !(e.KeyChar >= 'A' && e.KeyChar <= 'F'))
                        {
                            e.Handled = true;
                            return;
                        }
                        break;
                    }

                //zhu 2017-02-21
                case InputMod.NewHex:
                    {
                        if (   !Char.IsDigit(e.KeyChar) 
                            && !(e.KeyChar >= 'a' && e.KeyChar <= 'f')
                            && !(e.KeyChar >= 'A' && e.KeyChar <= 'F')
                            && !(e.KeyChar == 'x')
                            && !(e.KeyChar == 'X')
                            && !(e.KeyChar == '-'))
                        {
                            e.Handled = true;
                            return;
                        }
                        break;
                    }
                //---zhu 2017-02-21

                default: e.Handled = true; break;
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
#if DEBUG_ZHU
            txtStatus.Text = "打开Pcie驱动成功！\n";
#else
            if (PcieDriver.OpenPcieDevice() == false)
            {
                txtStatus.Text = "打开Pcie驱动失败！\n";
                txtStatus.Text += PcieDriver.GetLastDeviceError() + "\n";
                MessageBox.Show("打开Pcie驱动失败！", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
                txtStatus.Text = "打开Pcie驱动成功！\n";
#endif
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
#if DEBUG_ZHU
#else
            PcieDriver.ClosePcieDevice();
#endif
        }

        private void btnDmaFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog chaOpeFilDia = new OpenFileDialog();
            chaOpeFilDia.Filter = "bin files(*.bin)|*.bin|All files(*.*)|*.*";
            chaOpeFilDia.AddExtension = true;
            chaOpeFilDia.RestoreDirectory = true;
            if (chaOpeFilDia.ShowDialog() == DialogResult.OK)
            {
                txtDmaFile.Text = chaOpeFilDia.FileName;
                tipShow.SetToolTip(txtDmaFile, chaOpeFilDia.FileName);
            }
        }

        private void btnDmaLaun_Click(object sender, EventArgs e)
        {
            Button btn = sender as Button;

            ArrayList list = new ArrayList();
            
            if (btn.Name == btnDmaLaun.Name)
            {
                txtStatus.Text += "开始DMA传输...\n";
                txtDmaTime.Text = "0";

                list.Add(1);
                list.Add(txtDmaFile.Text);
                bgwDmaTransfer.RunWorkerAsync(list);
                dmaTransfer.Text = "DMA传输";
            }
            else
            {
                txtStatus.Text += "开始动态加载...\n";
                txtDmaTime.Text = "0";

                list.Add(3);
                list.Add(txtDmaFile.Text);
                bgwDmaTransfer.RunWorkerAsync(list);
                dmaTransfer.Text = "动态加载";
            }
            

            timerDmaTransfer.Enabled = true;
            timerDmaTransfer.Start();

            
            dmaTransfer.ShowDialog(this);
        }

        private void bgwDmaTransfer_DoWork(object sender, DoWorkEventArgs e)
        {
            ArrayList list = e.Argument as ArrayList;
            uint mode =(uint)((int)list[0]);
            String dmaFilePath = list[1] as String;
            FileStream fs = null;
            BinaryReader br = null;
            byte[] buf;
            long bufSizeMax = PcieDriver.MAX_BUF_SIZE;
            uint bufCount, lenExtra, alignByte = 0x400;
            double lastSec = 0, lastCompleted = 0;

            e.Result = true;

            try
            {
                fs = new FileStream(dmaFilePath, FileMode.Open, FileAccess.Read);
                br = new BinaryReader(fs);

                bufCount = (uint)(fs.Length / bufSizeMax);
                lenExtra = (uint)(fs.Length % bufSizeMax);
                if ((lenExtra & (alignByte - 1)) != 0)
                    lenExtra = (lenExtra & ~(alignByte - 1)) + alignByte;

#if DEBUG_ZHU
#else
                if (mode == 1)
                {
                    if (PcieDriver.SetDebugRegister(2, 0x8, 0x1) == false)
                    {
                        swDmaTime.Stop();
                        e.Result = false;

                        MessageBox.Show("发送数据失败！", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                }
                else
                {
                    if (PcieDriver.SetDebugRegister(2, 0x8, 0x3) == false)
                    {
                        swDmaTime.Stop();
                        e.Result = false;

                        MessageBox.Show("发送数据失败！", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                }
#endif
                if (bufCount > 0)
                {
                    for (uint ii = 0; ii < bufCount; ii++)
                    {
                        swDmaTime.Start();   // zhu 开始计时

                        buf = new byte[bufSizeMax];
                        buf = br.ReadBytes(buf.Length);
#if DEBUG_ZHU
#else
                        

                        if (PcieDriver.DmaToDevice(buf) == false)
                        {
                            swDmaTime.Stop();
                            e.Result = false;

                            MessageBox.Show("发送数据失败！", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            return;
                        }
#endif
                        swDmaTime.Stop();

                        dmaSpeedMB = buf.Length / 1024.0 / 1024.0 / (swDmaTime.Elapsed.TotalSeconds - lastSec);
                        dmaSpeedMB = Math.Round(dmaSpeedMB,2);
                        lastSec = swDmaTime.Elapsed.TotalSeconds;

                        lastCompleted += buf.Length;
                        dmaCompleted = (int)Math.Round(lastCompleted / fs.Length * 100);
                    }
                }

                if (lenExtra > 0)
                {
                    swDmaTime.Start();   // zhu 开始计时

                    buf = new byte[lenExtra];
                    br.ReadBytes((int)lenExtra).CopyTo(buf, 0);
#if DEBUG_ZHU
#else
                    if (PcieDriver.DmaToDevice(buf) == false)
                    {
                        swDmaTime.Stop();
                        e.Result = false;

                        MessageBox.Show("发送数据失败！", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
#endif
                    swDmaTime.Stop();

                    dmaSpeedMB = buf.Length / 1024.0 / 1024.0 / (swDmaTime.Elapsed.TotalSeconds - lastSec);
                    dmaSpeedMB = Math.Round(dmaSpeedMB, 2);
                    lastSec = swDmaTime.Elapsed.TotalSeconds;

                    dmaCompleted = 100;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("发送数据失败！", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            finally
            {
                if (br != null)
                    br.Close();
                if (fs != null)
                    fs.Close();
            }
        }

        private void timerDmaTransfer_Tick(object sender, EventArgs e)
        {
            dmaTransfer.ShowProgress(dmaSpeedMB, dmaCompleted);
        }

        private void bgwDmaTransfer_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            timerDmaTransfer.Stop();

            double dmaSec = Math.Round(swDmaTime.Elapsed.TotalSeconds,2);
            txtDmaTime.Text = Convert.ToString(dmaSec);
            swDmaTime.Reset();

            dmaSpeedMB = 0;
            dmaCompleted = 0;
            dmaTransfer.ShowProgress(dmaSpeedMB, dmaCompleted);
            dmaTransfer.Hide();

            if ((bool)e.Result)
                txtStatus.Text += "DMA传输完成！\n";
            else
            {
                txtStatus.Text += "DMA传输失败！\n";
                txtStatus.Text += PcieDriver.GetLastDeviceError() + "\n";
            }
        }

        private void dgvRegWrite_EditingControlShowing(object sender, DataGridViewEditingControlShowingEventArgs e)
        {
            if (e.Control is DataGridViewTextBoxEditingControl)
            {
                TextBox txt = e.Control as TextBox;
                txt.VisibleChanged += new EventHandler(TextBoxEditingControl_VisibleChanged);
                txt.KeyPress += new KeyPressEventHandler(TextBoxEditingControl_KeyPress);
            }
        }

        private void TextBoxEditingControl_KeyPress(object sender, KeyPressEventArgs e)
        {
            TextBox txt = sender as TextBox;
            if ("物理地址" == dgvRegWrite.Columns[dgvRegWrite.CurrentCell.ColumnIndex].HeaderText)
            {
                if (txt.SelectionStart < 2)
                    txt.SelectionStart = 2;

                InputLimit(txt, e, InputMod.Hex);

                if (e.KeyChar == '\b' && txt.SelectionLength == 0 && txt.SelectionStart < 3)
                    e.Handled = true;
            }
            else
                //zhu 2017-02-21
                //InputLimit(txt, e, InputMod.UInt);
                InputLimit(txt, e, InputMod.NewHex);
               
        }

        private void TextBoxEditingControl_VisibleChanged(object sender, EventArgs e)
        {
            TextBox txt = sender as TextBox;
            if (txt.Visible == false)
            {
                txt.VisibleChanged -= new EventHandler(TextBoxEditingControl_VisibleChanged);
                txt.KeyPress -= new KeyPressEventHandler(TextBoxEditingControl_KeyPress);
            }
        }

        private void 添加行ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int addRowsNum, rowStart, leaveRow = 0;
            int[] rowsIdx = new int[dgvRegWrite.SelectedRows.Count];

            rowStart = dgvRegWrite.Rows.Count - 1;
            for (int ii = 0; ii < dgvRegWrite.SelectedRows.Count; ii++)
                rowsIdx[ii] = dgvRegWrite.SelectedRows[ii].Index;
            Array.Sort(rowsIdx);

            if (rowsIdx[rowsIdx.Length - 1] == dgvRegWrite.RowCount - 1)
                leaveRow = 1;

            addRowsNum = dgvRegWrite.SelectedRows.Count - leaveRow;
            dgvRegWrite.RowCount += addRowsNum;

            for (int ii = 0; ii < addRowsNum; ii++)
            {
                for (int jj = 0; jj < dgvRegWrite.ColumnCount; jj++)
                    dgvRegWrite[jj, rowStart + ii].Value = dgvRegWrite[jj, rowsIdx[ii]].EditedFormattedValue.ToString();
            }
        }

        private void 删除行ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int[] rowsIdx = new int[dgvRegWrite.SelectedRows.Count];
            int leaveRow = 0;
            for (int ii = 0; ii < dgvRegWrite.SelectedRows.Count; ii++)
                rowsIdx[ii] = dgvRegWrite.SelectedRows[ii].Index;
            Array.Sort(rowsIdx);

            if (rowsIdx[rowsIdx.Length - 1] == dgvRegWrite.RowCount - 1)
                leaveRow = 1;

            for (int ii = rowsIdx.Length - 1 - leaveRow; ii >= 0; ii--)
            {
                dgvRegWrite.Rows.RemoveAt(rowsIdx[ii]);
            }
        }

        private void 保存表格ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FileStream listSaveFile = null;
            StreamWriter listSaveWrite = null;

            SaveFileDialog chaSavFilDia = new SaveFileDialog();
            chaSavFilDia.DefaultExt = "txt";
            chaSavFilDia.Filter = "(*.txt)|*.txt";
            chaSavFilDia.AddExtension = true;
            chaSavFilDia.RestoreDirectory = true;

            try
            {
                if (chaSavFilDia.ShowDialog() == DialogResult.OK)
                {
                    listSaveFile = new FileStream(chaSavFilDia.FileName, FileMode.OpenOrCreate);
                    listSaveWrite = new StreamWriter(listSaveFile);
                    for (int ii = 0; ii < dgvRegWrite.Rows.Count; ii++)
                    {
                        listSaveWrite.WriteLine(dgvRegWrite.Rows[ii].Cells[1].EditedFormattedValue.ToString() + "\t" +
                                                dgvRegWrite.Rows[ii].Cells[2].EditedFormattedValue.ToString() + "\t" +
                                                dgvRegWrite.Rows[ii].Cells[3].EditedFormattedValue.ToString());
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("保存表格失败！", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            finally
            {
                if (listSaveWrite != null)
                    listSaveWrite.Close();
                if (listSaveFile != null)
                    listSaveFile.Close();
            }
        }

        private void 载入表格ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string listData;
            int ii;
            FileStream listSaveFile = null;
            StreamReader listSaveRead = null;

            OpenFileDialog chaOpeFilDia = new OpenFileDialog();
            chaOpeFilDia.DefaultExt = "txt";
            chaOpeFilDia.Filter = "(*.txt)|*.txt";
            chaOpeFilDia.AddExtension = true;
            chaOpeFilDia.RestoreDirectory = true;

            try
            {
                if (chaOpeFilDia.ShowDialog() == DialogResult.OK)
                {
                    listSaveFile = new FileStream(chaOpeFilDia.FileName, FileMode.Open);
                    listSaveRead = new StreamReader(listSaveFile);

                    listData = listSaveRead.ReadLine();
                    ii = 0;
                    while (null != listData)
                    {
                        if (ii + 1 == dgvRegWrite.Rows.Count) dgvRegWrite.Rows.Insert(ii, 1);
                        dgvRegWrite.Rows[ii].Cells[1].Value = listData.Substring(0, listData.IndexOf("\t"));
                        listData = listData.Remove(0, listData.IndexOf("\t") + 1);
                        dgvRegWrite.Rows[ii].Cells[2].Value = listData.Substring(0, listData.IndexOf("\t"));
                        listData = listData.Remove(0, listData.IndexOf("\t") + 1);
                        dgvRegWrite.Rows[ii].Cells[3].Value = listData;

                        ii++;
                        listData = listSaveRead.ReadLine();
                    }
                    dgvRegWrite.Rows.RemoveAt(dgvRegWrite.Rows.Count - 2);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("载入表格失败！", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            finally
            {
                if (listSaveRead != null)
                    listSaveRead.Close();
                if (listSaveFile != null)
                    listSaveFile.Close();
            }
        }

        private void dgvRegWrite_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop)) e.Effect = DragDropEffects.All;
            else e.Effect = DragDropEffects.None;
        }

        private void dgvRegWrite_DragDrop(object sender, DragEventArgs e)
        {
            string strFilePath = ((System.Array)e.Data.GetData(DataFormats.FileDrop)).GetValue(0).ToString();
            string listData;
            int ii;
            FileStream listSaveFile = null;
            StreamReader listSaveRead = null;

            try
            {
                listSaveFile = new FileStream(strFilePath, FileMode.Open);
                listSaveRead = new StreamReader(listSaveFile);

                listData = listSaveRead.ReadLine();
                ii = 0;
                while (null != listData)
                {
                    if (ii + 1 == dgvRegWrite.Rows.Count) dgvRegWrite.Rows.Insert(ii, 1);
                    dgvRegWrite.Rows[ii].Cells[1].Value = listData.Substring(0, listData.IndexOf("\t"));
                    listData = listData.Remove(0, listData.IndexOf("\t") + 1);
                    dgvRegWrite.Rows[ii].Cells[2].Value = listData.Substring(0, listData.IndexOf("\t"));
                    listData = listData.Remove(0, listData.IndexOf("\t") + 1);
                    dgvRegWrite.Rows[ii].Cells[3].Value = listData;

                    ii++;
                    listData = listSaveRead.ReadLine();
                }
                dgvRegWrite.Rows.RemoveAt(dgvRegWrite.Rows.Count - 2);
            }
            catch (Exception ex)
            {
                MessageBox.Show("载入表格失败！", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            finally
            {
                if (listSaveRead != null)
                    listSaveRead.Close();
                if (listSaveFile != null)
                    listSaveFile.Close();
            }
        }

        private void dgvRegWrite_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (0 == e.ColumnIndex)
            {
                //zhu 2017-03-10
                string fpgaWriteDataStr;
                

                uint fpgaAddrData, fpgaWriteData;
                bool isCheck       = (bool)  dgvRegWrite.Rows[e.RowIndex].Cells[0].EditedFormattedValue;
                string fpgaAddr    = (string)dgvRegWrite.Rows[e.RowIndex].Cells[1].EditedFormattedValue;
                string fpgaIsCheck = (string)dgvRegWrite.Rows[e.RowIndex].Cells[2].EditedFormattedValue;
                string fpgaNoCheck = (string)dgvRegWrite.Rows[e.RowIndex].Cells[3].EditedFormattedValue;

                //zhu 2017-02-21
                bool isHexIsCheck = fpgaIsCheck.StartsWith("0x");
                bool isHexNoCheck = fpgaNoCheck.StartsWith("0x");

                fpgaAddr = fpgaAddr.Remove(0, 2);
                if ("" == fpgaAddr)
                {
                    MessageBox.Show("地址栏不能为空!", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
                fpgaAddrData = Convert.ToUInt32(fpgaAddr, 16);

                if (true == isCheck)
                {
                    if ("" == fpgaIsCheck)
                    {
                        MessageBox.Show("数据栏不能为空!", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                  // zhu 2017-02-21
                  //  fpgaWriteData = Convert.ToUInt32(fpgaIsCheck);
                    if (isHexIsCheck) { fpgaWriteData = Convert.ToUInt32(fpgaIsCheck, 16);  }
                    else              { fpgaWriteData = Convert.ToUInt32(fpgaIsCheck); }

                    fpgaWriteDataStr = fpgaIsCheck;
                  //---zhu 2017-02-21
                }
                else
                {
                    if ("" == fpgaNoCheck)
                    {
                        MessageBox.Show("数据栏不能为空!", "警告", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                    //zhu 2017-02-21
                    //fpgaWriteData = Convert.ToUInt32(fpgaNoCheck);
                    if (isHexNoCheck) { fpgaWriteData = Convert.ToUInt32(fpgaNoCheck, 16); }
                    else              { fpgaWriteData = Convert.ToUInt32(fpgaNoCheck); }

                    fpgaWriteDataStr = fpgaNoCheck;
                   
                }

                //txtStatus.Text += "写入...\n0x" + fpgaAddr + ":" + fpgaWriteData.ToString() + "\n";
                txtStatus.Text += "写入...\n0x" + fpgaAddr + ":" + fpgaWriteDataStr + "\n";
#if DEBUG_ZHU
                txtStatus.Text += "成功！\n";
#else
                if (PcieDriver.SetDeviceRegister(fpgaAddrData, fpgaWriteData))
                    txtStatus.Text += "成功！\n";
                else
                {
                    txtStatus.Text += "失败！\n";
                    txtStatus.Text += PcieDriver.GetLastDeviceError() + "\n";
                }
#endif
            }
        }

        private void btnDebugSet_Click(object sender, EventArgs e)
        {
            String addrStr = tboxDebugAddr.Text;
            String dataStr = tboxDebugData.Text;
            UInt32 barX = 0;
            UInt32 addr = 0;
            UInt32 data = 0;

            

            try
            {
                barX = Convert.ToUInt32(tboxBarX.Text);

                if (addrStr.StartsWith("0x"))
                {
                    addrStr = addrStr.Remove(0, 2);
                    addr = Convert.ToUInt32(addrStr, 16);
                }
                else
                {
                    addr = Convert.ToUInt32(addrStr);
                }

                if (dataStr.StartsWith("0x"))
                {
                    dataStr = dataStr.Remove(0, 2);
                    data = Convert.ToUInt32(dataStr, 16);
                }
                else
                {
                    data = Convert.ToUInt32(dataStr);
                }
            }
            catch (Exception ex)
            {
                txtStatus.Text += ex.Message;
                return;
            }

            txtStatus.Text += "写入...\n bar:"+ barX + "  0x" + addrStr + ":" + data + "\n";
#if DEBUG_ZHU
            txtStatus.Text += "成功！\n";
#else
            if (PcieDriver.SetDebugRegister(barX, addr, data))
                    txtStatus.Text += "成功！\n";
                else
                {
                    txtStatus.Text += "失败！\n";
                    txtStatus.Text += PcieDriver.GetLastDeviceError() + "\n";
                }
#endif
        }

        private void tboxDebugAddr_KeyPress(object sender, KeyPressEventArgs e)
        {
            InputLimit(sender as TextBox, e, InputMod.NewHex);
        }

        private void tboxBarX_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '\b') return;
            else if (tboxBarX.Text.Length >= 1)
            {
                e.Handled = true;
                return;
            }
            else if (e.KeyChar == '0') return;
            else if (e.KeyChar == '1') return;
            else if (e.KeyChar == '2') return;
            else
            {
                e.Handled = true;
                return;
            }
        }

        private void 发送所有选中项ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int maxLen = dgvRegWrite.Rows.Count;
            uint[] addrAndData = new uint[maxLen*2];
            uint sendLen = 0;

            txtStatus.AppendText("发送FPGA控制字：\n");
            txtStatus.AppendText("地址\t数据\n");
            for (int i = 0; i < maxLen;i++ )
            {                
                bool isCheck = (bool)dgvRegWrite.Rows[i].Cells[0].EditedFormattedValue;

                uint fpgaAddrData, fpgaWriteData;
                string fpgaAddr = (string)dgvRegWrite.Rows[i].Cells[1].EditedFormattedValue;


                if ("0x" == fpgaAddr || "" == fpgaAddr) { continue; }

                if (true == isCheck)
                {
                    string fpgaIsCheck = (string)dgvRegWrite.Rows[i].Cells[2].EditedFormattedValue;

                    if ("" == fpgaIsCheck || "0x" == fpgaIsCheck) { continue; }

                    //fpgaAddr = fpgaAddr.Remove(0, 2);                    
                    fpgaAddrData = Convert.ToUInt32(fpgaAddr, 16);

                    bool isHexIsCheck = fpgaIsCheck.StartsWith("0x");
                    if (isHexIsCheck) { fpgaWriteData = Convert.ToUInt32(fpgaIsCheck, 16); }
                    else { fpgaWriteData = Convert.ToUInt32(fpgaIsCheck); }

                    addrAndData[i * 2] = fpgaAddrData;
                    addrAndData[1 + i * 2] = fpgaWriteData;

                    txtStatus.AppendText(fpgaAddr + "\t" + fpgaIsCheck + "\n");
                    sendLen += 1;
                }
                else {
                    string fpgaNoCheck = (string)dgvRegWrite.Rows[i].Cells[3].EditedFormattedValue;

                    if ("" == fpgaNoCheck || "0x" == fpgaNoCheck) { continue; }

                    fpgaAddrData = Convert.ToUInt32(fpgaAddr, 16);

                    bool isHexIsCheck = fpgaNoCheck.StartsWith("0x");
                    if (isHexIsCheck) { fpgaWriteData = Convert.ToUInt32(fpgaNoCheck, 16); }
                    else { fpgaWriteData = Convert.ToUInt32(fpgaNoCheck); }

                    addrAndData[i * 2] = fpgaAddrData;
                    addrAndData[1 + i * 2] = fpgaWriteData;

                    txtStatus.AppendText(fpgaAddr + "\t" + fpgaNoCheck + "\n");
                    sendLen += 1;
                }

            }
#if DEBUG_ZHU
            txtStatus.AppendText("发送成功！\n");
#else
            if (!PcieDriver.SetFPGARegister(addrAndData,sendLen))
            {
                txtStatus.AppendText("发送成功！\n");
            }
            else
            {
                txtStatus.AppendText("发送失败！\n");
                txtStatus.AppendText(PcieDriver.GetLastDeviceError());
                txtStatus.AppendText("\n");
            }
#endif
        }

    }
}

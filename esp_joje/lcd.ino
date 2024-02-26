
void lcd() {


  HCMAX7219.Clear();
  HCMAX7219.print7Seg(temp * 10, 1, 24);
  HCMAX7219.print7Seg(humd * 10,1, 19);
  HCMAX7219.Refresh();
}
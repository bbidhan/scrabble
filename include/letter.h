#ifndef LETTER_H
#define LETTER_H


class letter
{
    public:
      letter();
      letter(char nam, int num, int scr);
      virtual ~letter();
      void setVal(char nam, int num, int scr);
      void convertBlankTo(char);
      int getASCII();
      int getNum();
      int getScore();
      char getName();
      bool exists();
      void kill();
    protected:
    private:
      int number;//repitition
      int score;
      char name;
      int ascii;
};

#endif // LETTER_H

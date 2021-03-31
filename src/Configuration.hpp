#if CORE_DEBUG_LEVEL <= 1

#define Verbose_Print(t) NULL
#define Verbose_Print_Line(t) NULL

#else

#define Verbose_Print(t) Serial.print(F(t))
#define Verbose_Print_Line(t) Serial.println(F(t))

#endif
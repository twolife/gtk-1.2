
BEGIN {
  in_def=0;
  TI=0;
  delete type_names;
  delete type_nicks;
  delete type_flags;
  n_defs = 0;
}

(init == 0) {
  printf ("/* generated by makeenums.awk from \"%s\" */\n\n", FILENAME);
  init=1;
}

";" {
  sub (";.*", "");
}

/\(/ {
  if (in_def == 0)
    {
      if ($1 == "(define-enum")
	{
	  in_def = 1;
	  type_flags[TI]=0;
	}
      else if ($1 == "(define-flags")
	{
	  in_def = 1;
	  type_flags[TI]=1;
	}
    }
  else
    in_def += 1;
}

(in_def == 1) {
  VI = 0;
  delete value_names;
  delete value_nicks;
  
  type_nicks[TI] = $2;
  type_names[TI] = "GTK_TYPE";
  for (i = 0; i < length(type_nicks[TI]); i++)
    {
      ch = substr(type_nicks[TI], i + 1, 1);
      Ch = toupper(ch);
      if (Ch == ch)
	type_names[TI] = type_names[TI] "_" Ch;
      else
	type_names[TI] = type_names[TI] Ch;
    }
}

(in_def == 2) {
  value_nicks[VI] = tolower ($1);
  value_names[VI] = $2;
  kill_pat="[^-A-z0123456789_]+";
  while (match (value_nicks[VI],kill_pat))
    sub(kill_pat,"",value_nicks[VI]);
  while (match (value_names[VI],kill_pat))
    sub(kill_pat,"",value_names[VI]);
}

/\)/ {
  if (in_def > 0)
    {
      while (match($0,")"))
	{
	  sub(")","");
	  if (in_def == 2)
	    VI += 1;
	  if (in_def == 1)
	    {
	      TI += 1;
	    }
	  in_def -= 1;
	}
      
      if (in_def == 0)
	{
	  printf ("static GtkEnumValue enum_values_%s[] = {\n", type_nicks[TI-1]);
	  for (j = 0; value_names[j] != ""; j++)
	    {
	      printf ("  { %s, \"%s\", \"%s\" },\n",
		      value_names[j], value_names[j], value_nicks[j]);
	    }
	  printf ("  { 0, NULL, NULL },\n");
	  printf ("};\n");
	}
    }
}

END {
#  printf("%u{\n", TI);
  for (i = 0; i < TI; i++)
    {
#      printf("  { %s, \"%s\", %s, %s_values },\n",
#	     type_names[i], type_nicks[i],
#	     type_flags[i] ? "TRUE" : "FALSE",
#	     tolower(type_nicks[i]));
    }
#  printf("};\n");
}
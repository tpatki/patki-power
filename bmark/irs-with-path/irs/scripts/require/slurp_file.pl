sub slurp_file 
{
  local ($filename) = @_;
  local ($size, $i, $[);
  local (*TFILE);

  $[ = 1;

  $size = -s $filename; # $size is in bytes

  $i = int ($size / 35);

  open (TFILE, $filename) || &Abend("slurp_file","Can't open file $filename");

  if ($i > 100000) {
    $i = 1;
    while (<TFILE>) {
      $text[$i] = $_;
      $i++;
    }
  }
  else { # Read in the file to EOF.
    @text = <TFILE>;
  }

  if (!($text[$#text] =~ /\n/)) {
     close TFILE;
     open (TFILE, ">>$filename") || &ABend("slurp_file","Can't open file $filename.");
     print TFILE "\n";
     push(@text, pop(@text) . "\n");
  }
  close TFILE;

  $ln = 1;
  $lastln = $#text;

}

1;
################################################################################
#                          E N D   O F   F I L E
################################################################################

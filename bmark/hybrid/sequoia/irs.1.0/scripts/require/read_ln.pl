
sub read_ln 
{

  local ($line, $[);

  $[ = 1;

  if ($ln == 'first call') {
    $ln = $[;
  }

  if ($ln <= $lastln) {
    $line = $text[$ln];
    $ln_num = $ln;          # 1-origin line numbers !
    $ln++;
  }
  else {
    $line = '--EOF--';
  }

  $line;
}


1;
################################################################################
#                          E N D   O F   F I L E
################################################################################

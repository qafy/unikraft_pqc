

int main_speed_kem(int argc, char **argv);
int main_speed_sig(int argc, char **argv);
int main_speed_common(int argc, char **argv);

int main(int argc, char **argv)
{
    main_speed_kem(argc, argv);
    main_speed_sig(argc, argv);
    main_speed_common(argc, argv);
}
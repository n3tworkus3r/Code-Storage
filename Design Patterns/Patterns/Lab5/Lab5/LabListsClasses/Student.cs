namespace Lab5
{
    namespace LabListsClasses
    {
        [System.Serializable]
        record Student
        {
            public int Id { get; set; }
            public string Name { get; set; }
            public string Surname { get; set; }
            public string SecondName { get; set; }
            public bool IsMale { get; set; }
            public System.DateTime DoB { get; set; }
        }
    }
}

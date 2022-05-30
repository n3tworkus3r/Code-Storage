namespace Lab5
{
    namespace LabListsClasses
    {
        [System.Serializable]
        record AcGroup
        {
            public int Id { get; set; }
            public string Name { get; set; }
            public string SpecName { get; set; }
            public int CourseNum { get; set; }
        }
    }

}

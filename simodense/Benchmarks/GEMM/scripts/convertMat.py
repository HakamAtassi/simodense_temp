import scipy.io
import scipy.sparse
import os

if __name__=="__main__":
    for(root,dirs,files) in os.walk('../mats/.', topdown=True):
        for file in files:
            if file.endswith('.mtx'):
                # Load mtx file
                matrix = scipy.io.mmread(os.path.join(root, file))

                # Convert to csr format
                csr_matrix = scipy.sparse.csr_matrix(matrix)

                # Write to C file
                with open("../mats_c/"+os.path.splitext(file)[0] + '.c', 'w') as f:
                    f.write(f'#ifndef {os.path.splitext(file)[0].upper()}_C_\n')
                    f.write(f'#define {os.path.splitext(file)[0].upper()}_C_\n\n')

                    f.write('int values[] = {')
                    f.write(', '.join(map(str, map(int ,csr_matrix.data))))
                    f.write('};\n\n')

                    f.write('int row_ptr[] = {')
                    f.write(', '.join(map(str, csr_matrix.indptr)))
                    f.write('};\n\n')

                    f.write('int col_index[] = {')
                    f.write(', '.join(map(str, csr_matrix.indices)))
                    f.write('};\n\n')

                    f.write('#endif\n')

                    print(f"{file} C file generated successfully")
